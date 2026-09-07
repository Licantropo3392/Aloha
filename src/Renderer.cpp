#include "Renderer.h"

#include "glDebug.h"

void Renderer::Draw(const Shader& shader, const VertexArrayObject& VAO, const ElementBufferObject& EBO)
{
    shader.Bind();
    VAO.Bind();
    EBO.Bind();

    glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::ClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor(const float r, const float g, const float b, const float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor(const float color[4])
{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}