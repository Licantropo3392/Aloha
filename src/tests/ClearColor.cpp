#include <imgui.h>

#include "../Renderer.h"
#include "../Window.h"
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

#include "ClearColor.h"

namespace Tests
{
    ClearColor::ClearColor(const Window* window)
        : Test(window), m_ClearColor{0.0f, 0.0f, 0.0f, 1.0f}
    {
    }

    void ClearColor::OnUpdate()
    {
#ifdef TRACY_ENABLE
        ZoneScopedN("ClearColor::OnUpdate");
#endif
        Renderer::GetInstance().ClearColor(m_ClearColor);
    }

    void ClearColor::OnImGuiRender()
    {
#ifdef TRACY_ENABLE
        ZoneScopedN("ClearColor::OnImGuiRender");
#endif
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}
