#include "VertexBufferObject.h"

#include "glad/glad.h"
#include "glDebug.h"
#include "GLObjects.h"

VertexBufferObject::VertexBufferObject(const void* data, const unsigned int size)
    : m_Impl(std::make_unique<Impl>())
{
    glGenBuffers(1, &m_Impl->rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_Impl->rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    if (m_Impl)
        glDeleteBuffers(1, &m_Impl->rendererId);
}

VertexBufferObject::VertexBufferObject(VertexBufferObject&&) noexcept = default;

void VertexBufferObject::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Impl->rendererId);
}

void VertexBufferObject::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
