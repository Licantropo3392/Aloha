#ifndef LEARN_OPENGL_UNIFORMBUFFEROBJECT_H
#define LEARN_OPENGL_UNIFORMBUFFEROBJECT_H

#include <memory>

class UniformBufferObject
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
public:
    UniformBufferObject(unsigned int index, unsigned int size);
    ~UniformBufferObject();

    UniformBufferObject(const UniformBufferObject&) = delete;
    UniformBufferObject& operator=(const UniformBufferObject&) = delete;
    UniformBufferObject(UniformBufferObject&&) noexcept;
    UniformBufferObject& operator=(UniformBufferObject&&) = delete;

    void Bind() const;
    static void Unbind();

    void SetSubData(const void* data, unsigned int size, unsigned int offset) const;
};


#endif //LEARN_OPENGL_UNIFORMBUFFEROBJECT_H
