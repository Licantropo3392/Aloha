#include "VertexArrayObject.h"

#include "glDebug.h"

#include "VertexBufferLayout.h"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArrayObject::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}

void VertexArrayObject::AddBuffer(const VertexBufferObject& VBO, const VertexBufferLayout& layout) const
{
    Bind();
    VBO.Bind();
    const auto elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements->size(); i++)
    {
        const auto& [type, count, normalized] = elements->at(i);
        glVertexAttribPointer(i, count, type, normalized, layout.GetStride(), reinterpret_cast<const void*>(offset));
        glEnableVertexAttribArray(i);
        offset += count * VertexBufferElement::getTypeSize(type);
    }
}
