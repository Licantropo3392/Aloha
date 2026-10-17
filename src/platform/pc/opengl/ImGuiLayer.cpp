#include "ImGuiLayer.h"

#include <stdexcept>

#include <glad/glad.h>

#include "Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>
#endif

struct ImGuiLayer::Impl
{
    ImGuiIO* io = nullptr;
};

ImGuiLayer::ImGuiLayer(const Window& window)
    : m_Impl(std::make_unique<Impl>())
{
    const char* glslVersion = nullptr;
    const float mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_Impl->io = &ImGui::GetIO();
    m_Impl->io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    m_Impl->io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    m_Impl->io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_Impl->io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(mainScale);
    style.FontScaleDpi = mainScale;

    if (!ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true))
    {
        ImGui::DestroyContext();
        throw std::runtime_error("Failed to initialize the ImGui GLFW backend");
    }
    if (!ImGui_ImplOpenGL3_Init(glslVersion))
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        throw std::runtime_error("Failed to initialize the ImGui OpenGL backend");
    }
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin() const
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End() const
{
#ifdef TRACY_ENABLE
    ZoneScopedN("ImGuiLayer::Render");
#endif
    ImGui::Render();
#ifdef TRACY_ENABLE
    TracyGpuZone("ImGui");
#endif
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (m_Impl->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }
}

float ImGuiLayer::GetFramerate() const
{
    return m_Impl->io->Framerate;
}
