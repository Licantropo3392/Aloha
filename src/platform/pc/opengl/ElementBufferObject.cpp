#include "ElementBufferObject.h"

#include "glad/glad.h"
#include "glDebug.h"
#include "GLObjects.h"

ElementBufferObject::ElementBufferObject(const unsigned int* data, const unsigned int count)
    : m_Impl(std::make_unique<Impl>())
{
    m_Impl->count = count;
    glGenBuffers(1, &m_Impl->rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Impl->rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementBufferObject::~ElementBufferObject()
{
    if (m_Impl)
        glDeleteBuffers(1, &m_Impl->rendererId);
}

ElementBufferObject::ElementBufferObject(ElementBufferObject&&) noexcept = default;

void ElementBufferObject::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Impl->rendererId);
}

void ElementBufferObject::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int ElementBufferObject::GetCount() const
{
    return m_Impl->count;
}
