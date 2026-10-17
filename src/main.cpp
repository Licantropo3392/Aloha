#include "tests/ClearColor.h"
#include "tests/Boxes.h"
#include "tests/Phong.h"

#include "Window.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <tracy/Tracy.hpp>

static int SCR_WIDTH = 854;
static int SCR_HEIGHT = 480;

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

int main()
{
    tracy::SetThreadName("Main");
    TracyMessageL("Aloha started");

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
        FrameMark;
        {
            ZoneScopedN("Application Frame");

            if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
                window.SetShouldClose(true);

            {
                ZoneScopedN("Update and render test");
                if (currentTest)
                    currentTest->OnUpdate();
            }

            {
                ZoneScopedN("ImGui frame");
                imgui.Begin();

                if (currentTest)
                    currentTest->OnImGuiRender();

                ImGui::Begin("Settings");
                testMenu->OnImGuiRender();

                const float currentFrame = Window::GetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / imgui.GetFramerate(), imgui.GetFramerate());
                TracyPlot("FPS", imgui.GetFramerate());

                if (ImGui::Button("Close"))
                    window.SetShouldClose(true);

                ImGui::End();
                imgui.End();
            }
        }

        {
            ZoneScopedN("Present frame");
            window.SwapBuffers();
            Window::PollEvents();
        }
    }

    return 0;
}