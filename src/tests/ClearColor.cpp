#include <imgui.h>

#include "../Renderer.h"
#include "../Window.h"

#include "ClearColor.h"

namespace Tests
{
    ClearColor::ClearColor(const Window* window)
        : Test(window), m_ClearColor{0.0f, 0.0f, 0.0f, 1.0f}
    {
    }

    void ClearColor::OnUpdate()
    {
        Renderer::ClearColor(m_ClearColor);
    }

    void ClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}
