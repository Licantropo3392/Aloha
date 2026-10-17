#include "tests/ClearColor.h"
#include "tests/Boxes.h"
#include "tests/Phong.h"

#include "Window.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

static int SCR_WIDTH = 854;
static int SCR_HEIGHT = 480;

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

int main()
{
#ifdef TRACY_ENABLE
    tracy::SetThreadName("Main");
    TracyMessageL("Aloha started");
#endif

    const Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    const ImGuiLayer imgui(window);

    Tests::Test* currentTest = nullptr;
    const auto testMenu = new Tests::TestMenu(&window, currentTest);
    currentTest = testMenu;

    testMenu->Register<Tests::ClearColor>("Clear Color");
    testMenu->Register<Tests::Boxes>("Boxes");
    testMenu->Register<Tests::Phong>("Phong");

    while (!window.ShouldClose())
    {
#ifdef TRACY_ENABLE
        FrameMark;
#endif
        {
#ifdef TRACY_ENABLE
            ZoneScopedN("Application Frame");
#endif

            if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
                window.SetShouldClose(true);

            {
#ifdef TRACY_ENABLE
                ZoneScopedN("Update and render test");
#endif
                if (currentTest)
                    currentTest->OnUpdate();
            }

            {
#ifdef TRACY_ENABLE
                ZoneScopedN("ImGui frame");
#endif
                imgui.Begin();

                if (currentTest)
                    currentTest->OnImGuiRender();

                ImGui::Begin("Settings");
                testMenu->OnImGuiRender();

                const float currentFrame = Window::GetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / imgui.GetFramerate(), imgui.GetFramerate());
#ifdef TRACY_ENABLE
                TracyPlot("FPS", imgui.GetFramerate());
#endif

                if (ImGui::Button("Close"))
                    window.SetShouldClose(true);

                ImGui::End();
                imgui.End();
            }
        }

        {
#ifdef TRACY_ENABLE
            ZoneScopedN("Present frame");
#endif
            window.SwapBuffers();
            Window::PollEvents();
        }
    }

    return 0;
}