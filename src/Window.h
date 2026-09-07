#ifndef LEARN_OPENGL_WINDOW_H
#define LEARN_OPENGL_WINDOW_H


#include <string>
#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* m_Window;
    int m_Width, m_Height;

    mutable double m_X = 0;
    mutable double m_Y = 0;

public:
    Window(int width, int height, const std::string& title);
    ~Window();

    [[nodiscard]] bool ShouldClose() const;
    void SetShouldClose(bool shouldClose) const;
    void SetCursorNormal() const;
    void SetCursorDisabled() const;

    void SwapBuffers() const;
    static void PollEvents();

    [[nodiscard]] bool IsKeyPressed(int key) const;
    static float GetTime();

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void OnFramebufferSize(int width, int height);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    void OnMouseMove(double xpos, double ypos);
    // static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    // void OnScroll(double xoffset, double yoffset);

    [[nodiscard]] double GetMouseX() const;
    [[nodiscard]] double GetMouseY() const;

    [[nodiscard]] int GetWidth() const { return m_Width; }
    [[nodiscard]] int GetHeight() const { return m_Height; }
    [[nodiscard]] GLFWwindow* GetWindow() const { return m_Window; }
};


#endif //LEARN_OPENGL_WINDOW_H
