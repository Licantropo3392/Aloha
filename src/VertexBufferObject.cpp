#include "VertexBufferObject.h"

#include "glad/glad.h"
#include "glDebug.h"

VertexBufferObject::VertexBufferObject(const void* data, const unsigned int size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBufferObject::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBufferObject::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
