#ifndef LEARN_OPENGL_VERTEXBUFFERLAYOUT_H
#define LEARN_OPENGL_VERTEXBUFFERLAYOUT_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int getTypeSize(const unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:              return (unsigned int)sizeof(GLfloat);
            case GL_UNSIGNED_INT:       return (unsigned int)sizeof(GLuint);
            case GL_UNSIGNED_BYTE:      return (unsigned int)sizeof(GLubyte);
            case GL_UNSIGNED_SHORT:     return (unsigned int)sizeof(GLushort);
            case GL_BYTE:               return (unsigned int)sizeof(GLbyte);
            case GL_SHORT:              return (unsigned int)sizeof(GLshort);
            case GL_INT:                return (unsigned int)sizeof(GLint);
        }

        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride = 0;

public:
    template <typename T>
    void Push(int count)
    {
        static_assert(false, "VertexBufferLayout is not implemented for this type");
    }

    [[nodiscard]] const std::vector<VertexBufferElement>* GetElements() const
    {
        return &m_Elements;
    }

    [[nodiscard]] unsigned int GetStride() const
    {
        return m_Stride;
    }
};

template <>
inline void VertexBufferLayout::Push<float>(int count)
{
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::getTypeSize(GL_FLOAT);
}

template <>
inline void VertexBufferLayout::Push<unsigned int>(int count)
{
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_INT);
}

template <>
inline void VertexBufferLayout::Push<unsigned char>(int count)
{
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE);
}


#endif
