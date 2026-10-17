#pragma once

#include <memory>

class ElementBufferObject
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
public:
    ElementBufferObject(const unsigned int* data, unsigned int count);
    ~ElementBufferObject();

    ElementBufferObject(const ElementBufferObject&) = delete;
    ElementBufferObject& operator=(const ElementBufferObject&) = delete;
    ElementBufferObject(ElementBufferObject&&) noexcept;
    ElementBufferObject& operator=(ElementBufferObject&&) = delete;

    void Bind() const;
    static void Unbind();

    [[nodiscard]] unsigned int GetCount() const;
};
