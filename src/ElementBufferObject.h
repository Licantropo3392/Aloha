#ifndef LEARN_OPENGL_ELEMENTBUFFEROBJECT_H
#define LEARN_OPENGL_ELEMENTBUFFEROBJECT_H


class ElementBufferObject
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count {};
public:
    ElementBufferObject(const unsigned int* data, unsigned int count);
    ~ElementBufferObject();

    void Bind() const;
    static void Unbind();

    [[nodiscard]] unsigned int GetCount() const
    {
        return m_Count;
    }
};


#endif //LEARN_OPENGL_ELEMENTBUFFEROBJECT_H
