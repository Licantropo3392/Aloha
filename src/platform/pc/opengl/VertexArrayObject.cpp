#include "VertexArrayObject.h"

#include <cstdint>
#include <stdexcept>

#include "glDebug.h"
#include "GLObjects.h"

#include "VertexBufferLayout.h"

namespace
{
    unsigned int ToOpenGLType(const VertexAttributeType type)
    {
        switch (type)
        {
            case VertexAttributeType::Float32: return GL_FLOAT;
            case VertexAttributeType::UInt32:  return GL_UNSIGNED_INT;
            case VertexAttributeType::UInt8:   return GL_UNSIGNED_BYTE;
        }

        throw std::invalid_argument("Unsupported vertex attribute type");
    }
}

VertexArrayObject::VertexArrayObject()
    : m_Impl(std::make_unique<Impl>())
{
    glGenVertexArrays(1, &m_Impl->rendererId);
    glBindVertexArray(m_Impl->rendererId);
}

VertexArrayObject::~VertexArrayObject()
{
    if (m_Impl)
        glDeleteVertexArrays(1, &m_Impl->rendererId);
}

VertexArrayObject::VertexArrayObject(VertexArrayObject&&) noexcept = default;

void VertexArrayObject::Bind() const
{
    glBindVertexArray(m_Impl->rendererId);
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
        glVertexAttribPointer(i, count, ToOpenGLType(type), normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(), reinterpret_cast<const void*>(static_cast<std::uintptr_t>(offset)));
        glEnableVertexAttribArray(i);
        offset += count * VertexBufferElement::GetTypeSize(type);
    }
}
