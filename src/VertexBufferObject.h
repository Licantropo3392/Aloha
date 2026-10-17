#ifndef LEARN_OPENGL_VERTEXBUFFEROBJECT_H
#define LEARN_OPENGL_VERTEXBUFFEROBJECT_H

#include <memory>

class VertexBufferObject
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
public:
    VertexBufferObject(const void* data, unsigned int size);
    ~VertexBufferObject();

    VertexBufferObject(const VertexBufferObject&) = delete;
    VertexBufferObject& operator=(const VertexBufferObject&) = delete;
    VertexBufferObject(VertexBufferObject&&) noexcept;
    VertexBufferObject& operator=(VertexBufferObject&&) = delete;

    void Bind() const;
    static void Unbind();
};


#endif //LEARN_OPENGL_VERTEXBUFFEROBJECT_H
