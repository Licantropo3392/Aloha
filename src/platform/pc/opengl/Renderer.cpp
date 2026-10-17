#include "Renderer.h"

#include "glDebug.h"
#include "GLObjects.h"
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>
#endif

Renderer::Renderer()
    : m_Impl(std::make_unique<Impl>())
{
}

Renderer::~Renderer() = default;

Renderer& Renderer::GetInstance()
{
    static Renderer instance;
    return instance;
}

void Renderer::Draw(const Shader& shader, const VertexArrayObject& VAO, const ElementBufferObject& EBO) const
{
#ifdef TRACY_ENABLE
    ZoneScopedN("Renderer::Draw");
    TracyGpuZone("Draw");
#endif
    shader.Bind();
    VAO.Bind();
    EBO.Bind();

    glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::ClearColor(const glm::vec4& color) const
{
#ifdef TRACY_ENABLE
    ZoneScopedN("Renderer::Clear");
    TracyGpuZone("Clear");
#endif
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor(const float r, const float g, const float b, const float a) const
{
#ifdef TRACY_ENABLE
    ZoneScopedN("Renderer::Clear");
    TracyGpuZone("Clear");
#endif
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor(const float color[4]) const
{
#ifdef TRACY_ENABLE
    ZoneScopedN("Renderer::Clear");
    TracyGpuZone("Clear");
#endif
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}