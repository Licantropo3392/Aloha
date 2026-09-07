#ifndef LEARN_OPENGL_BOXES_H
#define LEARN_OPENGL_BOXES_H


#include "../Test.h"

#include "../Shader.h"
#include "../camera.h"
#include "../MVP.h"

#include "../Texture.h"

#include "../VertexArrayObject.h"
#include "../VertexBufferObject.h"
#include "../ElementBufferObject.h"
#include "../UniformBufferObject.h"

#include "../Window.h"

namespace Tests
{
    class Boxes : public Test
    {
    private:
        Shader* m_Shader;
        Camera* m_Camera;
        MVP* m_MVP {};

        Texture* m_Container;
        Texture* m_Face;

        VertexArrayObject* m_VAO;
        VertexBufferObject* m_VBO;
        ElementBufferObject* m_EBO;
        UniformBufferObject* m_UBO;

        std::vector<glm::vec3> m_CubePositions;

        double m_LastX, m_LastY;

    public:
        explicit Boxes(const Window* window);
        ~Boxes() override;

        void OnUpdate() override;
        void OnImGuiRender() override;
    };
}

#endif //LEARN_OPENGL_BOXES_H
