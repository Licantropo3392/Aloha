#include "ElementBufferObject.h"

#include "glad/glad.h"
#include "glDebug.h"

ElementBufferObject::ElementBufferObject(const unsigned int* data, const unsigned int count)
    : m_Count(count)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementBufferObject::~ElementBufferObject()
{
    glDeleteBuffers(1, &m_RendererID);
}

void ElementBufferObject::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void ElementBufferObject::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
