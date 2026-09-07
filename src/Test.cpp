#include <imgui.h>

#include "Renderer.h"
#include "Window.h"

#include "Test.h"

namespace Tests
{
    Test::Test(const Window* window)
        : m_Window(window)
    { }

    TestMenu::TestMenu(const Window* window, Test*& currentTest)
        : Test(window), m_CurrentTest(currentTest)
    { }

    void TestMenu::OnUpdate()
    {
        Renderer::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void TestMenu::OnImGuiRender()
    {
        for (auto& [name, ptr] : m_Tests)
        {
            if (ImGui::Button(name.c_str()))
                m_CurrentTest = ptr();
        }
    }
}
