#ifndef LEARN_OPENGL_VERTEXARRAYOBJECT_H
#define LEARN_OPENGL_VERTEXARRAYOBJECT_H


#include "VertexBufferObject.h"

class VertexBufferLayout;

class VertexArrayObject
{
private:
    unsigned int m_RendererID;
    unsigned int m_NextAttribIndex = 0;
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void Bind() const;
    static void Unbind() ;

    void AddBuffer(const VertexBufferObject& VBO, const VertexBufferLayout& layout) const;
};


#endif //LEARN_OPENGL_VERTEXARRAYOBJECT_H
