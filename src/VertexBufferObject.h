#ifndef LEARN_OPENGL_VERTEXBUFFEROBJECT_H
#define LEARN_OPENGL_VERTEXBUFFEROBJECT_H


class VertexBufferObject
{
private:
    unsigned int m_RendererID;
public:
    VertexBufferObject(const void* data, unsigned int size);
    ~VertexBufferObject();

    void Bind() const;
    static void Unbind();
};


#endif //LEARN_OPENGL_VERTEXBUFFEROBJECT_H
