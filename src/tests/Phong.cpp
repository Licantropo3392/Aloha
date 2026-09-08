#include "Phong.h"

#include "../Shader.h"
#include "Camera.h"
#include "../MVP.h"

#include "../Texture.h"

#include "../VertexArrayObject.h"
#include "../VertexBufferObject.h"
#include "../ElementBufferObject.h"
#include "../VertexBufferLayout.h"
#include "../UniformBufferObject.h"

#include "../Renderer.h"
#include "../Window.h"
#include <imgui.h>

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

namespace Tests
{
    Phong::Phong(const Window* window)
        : Test(window)
    {
        m_Window = window;

        m_Shader = new Shader("assets/shaders/Phong.shader");
        m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

        m_MVP = new MVP();

        constexpr float vertices[] = {
            // Back face (z = -0.5)     // Texture          // Normals
            -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,          0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,        1.0f, 0.0f,          0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,        1.0f, 1.0f,          0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,        0.0f, 1.0f,          0.0f,  0.0f, -1.0f,

            // Front face (z = 0.5)
            -0.5f, -0.5f, 0.5f,         0.0f, 0.0f,          0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, 0.5f,         1.0f, 0.0f,          0.0f,  0.0f,  1.0f,
             0.5f,  0.5f, 0.5f,         1.0f, 1.0f,          0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f, 0.5f,         0.0f, 1.0f,          0.0f,  0.0f,  1.0f,

            // Left face (x = -0.5)
            -0.5f,  0.5f,  0.5f,        1.0f, 0.0f,         -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,        1.0f, 1.0f,         -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,         -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,         -1.0f,  0.0f,  0.0f,

            // Right face (x = 0.5)
             0.5f,  0.5f,  0.5f,        1.0f, 0.0f,          1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,        1.0f, 1.0f,          1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,        0.0f, 1.0f,          1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,        0.0f, 0.0f,          1.0f,  0.0f,  0.0f,

            // Bottom face (y = -0.5)
            -0.5f, -0.5f, -0.5f,        0.0f, 1.0f,          0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,        1.0f, 1.0f,          0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,        1.0f, 0.0f,          0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,          0.0f, -1.0f,  0.0f,

            // Top face (y = 0.5)
            -0.5f,  0.5f, -0.5f,         0.0f, 1.0f,         0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,         1.0f, 1.0f,         0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,         1.0f, 0.0f,         0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,         0.0f, 0.0f,         0.0f,  1.0f,  0.0f
        };

        constexpr unsigned int indices[36] = {
             0,  1,  2,  2,  3,  0,   // back
             4,  5,  6,  6,  7,  4,   // front
             8,  9, 10, 10, 11,  8,   // left
            12, 13, 14, 14, 15, 12,   // right
            16, 17, 18, 18, 19, 16,   // bottom
            20, 21, 22, 22, 23, 20    // top
        };

        m_CubePositions = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
        };

        m_Container = new Texture("assets/container.jpg");
        m_Face = new Texture("assets/awesomeface.png");

        m_VAO = new VertexArrayObject();
        m_VBO = new VertexBufferObject(vertices, sizeof(vertices));
        m_EBO = new ElementBufferObject(indices, sizeof(indices) / sizeof(unsigned int));
        VertexBufferLayout layout{};
        m_UBO = new UniformBufferObject(sizeof(*m_MVP), sizeof(glm::mat4));

        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(3);
        m_VAO->AddBuffer(*m_VBO, layout);

        m_Shader->Bind();

        m_Container->Bind();
        m_Face->Bind(1);

        m_Shader->SetUniform("texture1", 0);
        m_Shader->SetUniform("texture2", 1);
        m_Shader->SetUniform("lightPos", 0.0f, 0.0f, 1.0f);

        m_Window->SetCursorDisabled();
        m_LastX = m_Window->GetMouseX();
        m_LastY = m_Window->GetMouseY();
    }

    Phong::~Phong()
    {
        delete m_Shader;
        delete m_Camera;
        delete m_MVP;

        delete m_Container;
        delete m_Face;

        delete m_VAO;
        delete m_VBO;
        delete m_EBO;
        delete m_UBO;
    }

    void Phong::OnUpdate()
    {
        Renderer::ClearColor();

        const float currentFrame = Window::GetTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (m_Window->IsKeyPressed(GLFW_KEY_ESCAPE))
            m_Window->SetShouldClose(true);

        if (m_Window->IsKeyPressed(GLFW_KEY_W))
            m_Camera->ProcessKeyboard(FORWARD, deltaTime);
        if (m_Window->IsKeyPressed(GLFW_KEY_S))
            m_Camera->ProcessKeyboard(BACKWARD, deltaTime);
        if (m_Window->IsKeyPressed(GLFW_KEY_A))
            m_Camera->ProcessKeyboard(LEFT, deltaTime);
        if (m_Window->IsKeyPressed(GLFW_KEY_D))
            m_Camera->ProcessKeyboard(RIGHT, deltaTime);

        if (m_Window->IsKeyPressed(GLFW_KEY_ENTER))
            m_Window->SetCursorDisabled();
        if (m_Window->IsKeyPressed(GLFW_KEY_BACKSPACE))
            m_Window->SetCursorNormal();

        const auto mouseX = m_Window->GetMouseX();
        const auto mouseY = m_Window->GetMouseY();
        m_Camera->ProcessMouseMovement(mouseX - m_LastX, m_LastY - mouseY);
        m_LastX = mouseX;
        m_LastY = mouseY;

        m_MVP->projection = glm::perspective(glm::radians(m_Camera->GetZoom()), static_cast<float>(m_Window->GetWidth()) / static_cast<float>(m_Window->GetHeight()), 0.1f, 100.0f);
        m_MVP->view = m_Camera->GetViewMatrix();

        m_Shader->SetUniform("viewPos", m_Camera->GetPosition());

        for (unsigned int i = 0; i < m_CubePositions.size(); i++)
        {
            m_MVP->model = glm::mat4(1.0f);
            m_MVP->model = glm::translate(m_MVP->model, m_CubePositions.at(i));
            const float angle = 20.0f * i;
            m_MVP->model = glm::rotate(m_MVP->model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            m_UBO->SetSubData(&m_MVP->model, sizeof(glm::mat4), 0);
            m_UBO->SetSubData(&m_MVP->view, sizeof(glm::mat4), sizeof(glm::mat4));
            m_UBO->SetSubData(&m_MVP->projection, sizeof(glm::mat4), sizeof(glm::mat4) * 2);

            Renderer::Draw(*m_Shader, *m_VAO, *m_EBO);
        }
    }

    void Phong::OnImGuiRender()
    {
        // static float f = 0.0f;
        //
        // ImGui::Begin("Vertex Positions");
        //
        // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        //
        // ImGui::End();
    }
}