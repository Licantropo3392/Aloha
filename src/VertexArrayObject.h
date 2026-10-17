#pragma once


#include <memory>

#include "VertexBufferObject.h"

class VertexBufferLayout;

class VertexArrayObject
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
public:
    VertexArrayObject();
    ~VertexArrayObject();

    VertexArrayObject(const VertexArrayObject&) = delete;
    VertexArrayObject& operator=(const VertexArrayObject&) = delete;
    VertexArrayObject(VertexArrayObject&&) noexcept;
    VertexArrayObject& operator=(VertexArrayObject&&) = delete;

    void Bind() const;
    static void Unbind() ;

    void AddBuffer(const VertexBufferObject& VBO, const VertexBufferLayout& layout) const;
};
