#ifndef LEARN_OPENGL_RENDERER_H
#define LEARN_OPENGL_RENDERER_H

#include <glm/vec4.hpp>

#include "Shader.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"

class Renderer
{
public:
    static void Draw(const Shader& shader, const VertexArrayObject& VAO, const ElementBufferObject& EBO);
    static void ClearColor(const glm::vec4& color = glm::vec4(0));
    static void ClearColor(float r, float g, float b, float a);
    static void ClearColor(const float color[4]);
};


#endif //LEARN_OPENGL_RENDERER_H
