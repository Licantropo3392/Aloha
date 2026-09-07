#ifndef LEARN_OPENGL_UNIFORMBUFFEROBJECT_H
#define LEARN_OPENGL_UNIFORMBUFFEROBJECT_H


class UniformBufferObject
{
private:
    unsigned int m_RendererID;
public:
    UniformBufferObject(unsigned int size, unsigned int rangeSize);
    ~UniformBufferObject();

    void Bind() const;
    static void Unbind();

    void SetSubData(const void* data, unsigned int size, unsigned int offset) const;
};


#endif //LEARN_OPENGL_UNIFORMBUFFEROBJECT_H
