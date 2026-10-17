#pragma once


#include <cstddef>
#include <vector>

enum class VertexAttributeType
{
    Float32,
    UInt32,
    UInt8
};

struct VertexBufferElement
{
    VertexAttributeType type;
    unsigned int count;
    bool normalized;

    [[nodiscard]] static constexpr std::size_t GetTypeSize(const VertexAttributeType type)
    {
        switch (type)
        {
            case VertexAttributeType::Float32: return sizeof(float);
            case VertexAttributeType::UInt32:  return sizeof(unsigned int);
            case VertexAttributeType::UInt8:   return sizeof(unsigned char);
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
    void Push(unsigned int count)
    {
        static_assert(!sizeof(T), "VertexBufferLayout is not implemented for this type");
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
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({ VertexAttributeType::Float32, count, false });
    m_Stride += count * VertexBufferElement::GetTypeSize(VertexAttributeType::Float32);
}

template <>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({ VertexAttributeType::UInt32, count, false });
    m_Stride += count * VertexBufferElement::GetTypeSize(VertexAttributeType::UInt32);
}

template <>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({ VertexAttributeType::UInt8, count, true });
    m_Stride += count * VertexBufferElement::GetTypeSize(VertexAttributeType::UInt8);
}
