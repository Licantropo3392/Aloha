#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glDebug.h"

#include "Window.h"

bool debugContext;

Window::Window(int width, int height, const std::string& title)
    : m_Width(width), m_Height(height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (m_Window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_Window);

    glfwSetWindowUserPointer(m_Window, this);
    glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
    // glfwSetCursorPosCallback(m_Window, MouseCallback);
    // glfwSetScrollCallback(m_Window, scroll_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSwapInterval(1); // Enable vsync

#ifndef NDEBUG
    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        debugContext = true;

        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif

    glfwGetFramebufferSize(m_Window, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

void Window::SetShouldClose(const bool shouldClose) const
{
    glfwSetWindowShouldClose(m_Window, shouldClose);
}

void Window::SetCursorNormal() const
{
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::SetCursorDisabled() const
{
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

bool Window::IsKeyPressed(const int key) const
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

float Window::GetTime()
{
    return static_cast<float>(glfwGetTime());
}

void Window::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    self->OnFramebufferSize(width, height);
}

void Window::OnFramebufferSize(const int width, const int height)
{
    glViewport(0, 0, width, height);
    m_Width = width;
    m_Height = height;
}

// void Window::MouseCallback(GLFWwindow* window, const double xpos, const double ypos)
// {
//     auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//     self->OnMouseMove(xpos, ypos);
// }

double Window::GetMouseX() const
{
    glfwGetCursorPos(m_Window, &m_X, &m_Y);
    return m_X;
}

double Window::GetMouseY() const
{
    glfwGetCursorPos(m_Window, &m_X,&m_Y);
    return m_Y;
}

// void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
// {
//     auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//     self->OnScroll(xoffset, yoffset);
// }
//
// void Window::OnScroll(double xoffset, double yoffset)
// {
//     camera.ProcessMouseScroll(static_cast<float>(yoffset));
// }