#ifndef LEARN_OPENGL_IMGUILAYER_H
#define LEARN_OPENGL_IMGUILAYER_H


#include <imgui_impl_glfw.h>
#include "GLFW/glfw3.h"

class ImGuiLayer
{
private:
    GLFWwindow* m_Window;
    ImGuiIO* m_IO;

public:
    explicit ImGuiLayer(GLFWwindow* window);
    ~ImGuiLayer();

    static void Begin();
    void End() const;

    [[nodiscard]] ImGuiIO* GetIO() const
    {
        return m_IO;
    }
};


#endif
