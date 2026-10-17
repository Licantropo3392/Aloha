#pragma once

#include <memory>

#include <glm/vec4.hpp>

#include "Shader.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"

class Renderer
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;

    Renderer();
    ~Renderer();

public:
    [[nodiscard]] static Renderer& GetInstance();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void Draw(const Shader& shader, const VertexArrayObject& VAO, const ElementBufferObject& EBO) const;
    void ClearColor(const glm::vec4& color = glm::vec4(0)) const;
    void ClearColor(float r, float g, float b, float a) const;
    void ClearColor(const float color[4]) const;
};
