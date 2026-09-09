#include "tests/ClearColor.h"
#include "tests/Boxes.h"
#include "tests/Phong.h"

#include "Window.h"
#include "ImGuiLayer.h"

#include <tracy/Tracy.hpp>

static int SCR_WIDTH = 854;
static int SCR_HEIGHT = 480;

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

int main()
{
    const Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    const ImGuiLayer imgui(window.GetWindow());

    Tests::Test* currentTest = nullptr;
    const auto testMenu = new Tests::TestMenu(&window, currentTest);
    currentTest = testMenu;

    testMenu->Register<Tests::ClearColor>("Clear Color");
    testMenu->Register<Tests::Boxes>("Boxes");
    testMenu->Register<Tests::Phong>("Phong");

    while (!window.ShouldClose())
    {
        if (currentTest)
        {
            currentTest->OnUpdate();
            ImGuiLayer::Begin();

            // ImGui::ShowDemoWindow();
            ImGui::Begin("Settings");
            testMenu->OnImGuiRender();

            const float currentFrame = Window::GetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / imgui.GetIO()->Framerate, imgui.GetIO()->Framerate);
            ImGui::End();

            currentTest->OnImGuiRender();

            imgui.End();
        }

        FrameMark;

        window.SwapBuffers();
        Window::PollEvents();
    }

    return 0;
}