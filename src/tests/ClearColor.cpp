#include <imgui.h>

#include "../Renderer.h"
#include "../Window.h"
#include <tracy/Tracy.hpp>

#include "ClearColor.h"

namespace Tests
{
    ClearColor::ClearColor(const Window* window)
        : Test(window), m_ClearColor{0.0f, 0.0f, 0.0f, 1.0f}
    {
    }

    void ClearColor::OnUpdate()
    {
        ZoneScopedN("ClearColor::OnUpdate");
        Renderer::GetInstance().ClearColor(m_ClearColor);
    }

    void ClearColor::OnImGuiRender()
    {
        ZoneScopedN("ClearColor::OnImGuiRender");
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}
