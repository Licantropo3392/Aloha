#include <imgui.h>

#include <utility>

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

    static const char* item_current = nullptr;
    void TestMenu::OnImGuiRender()
    {
        if (item_current == nullptr)
        {
            m_CurrentTest = m_Tests[0].second();
            item_current = m_Tests[0].first.c_str();
        }

        if (ImGui::BeginCombo("Tests", item_current))
        {
            for (const auto& [name, ptr] : m_Tests)
            {
                const bool is_selected = (item_current == name.c_str());
                if (ImGui::Selectable(name.c_str(), is_selected))
                {
                    item_current = name.c_str();
					m_CurrentTest = ptr();
                }

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
}
