#include "UniformBufferObject.h"

#include "glad/glad.h"
#include "glDebug.h"

UniformBufferObject::UniformBufferObject(const unsigned int size, const unsigned int rangeSize)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_RendererID, 0, rangeSize);
}

UniformBufferObject::~UniformBufferObject()
{
    glDeleteBuffers(1, &m_RendererID);
}

void UniformBufferObject::Bind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
}

void UniformBufferObject::Unbind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferObject::SetSubData(const void* data, const unsigned int size, const unsigned int offset) const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

// void UniformBufferObject::SetData(const void* data) const
// {
//     glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
//
//     for (unsigned int i = 0; i < ; i++)
//     glBufferSubData(GL_UNIFORM_BUFFER, 0, m_RendererID, sizeof(data));
// }