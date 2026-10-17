#include "UniformBufferObject.h"

#include "glad/glad.h"
#include "glDebug.h"
#include "GLObjects.h"

UniformBufferObject::UniformBufferObject(const unsigned int index, const unsigned int size)
    : m_Impl(std::make_unique<Impl>())
{
    glGenBuffers(1, &m_Impl->rendererId);
    glBindBuffer(GL_UNIFORM_BUFFER, m_Impl->rendererId);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, index, m_Impl->rendererId, 0, size);
}

UniformBufferObject::~UniformBufferObject()
{
    if (m_Impl)
        glDeleteBuffers(1, &m_Impl->rendererId);
}

UniformBufferObject::UniformBufferObject(UniformBufferObject&&) noexcept = default;

void UniformBufferObject::Bind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_Impl->rendererId);
}

void UniformBufferObject::Unbind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferObject::SetSubData(const void* data, const unsigned int size, const unsigned int offset) const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_Impl->rendererId);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}