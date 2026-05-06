#include <Window/platform.hpp>

#include <raylib.h>

namespace Aloha::WindowImpl
{
    void create(int screenWidth, int screenHeight, const char *title)
    {
        InitWindow(screenWidth, screenHeight, title);
    }

    void setFPS(int fps)
    {
        SetTargetFPS(fps);
    }

    void close()
    {
        CloseWindow();
    }

    bool shouldClose()
    {
        return WindowShouldClose();
    }

    void beginDrawing(Color color)
    {
        BeginDrawing();
        ClearBackground({color.r, color.g, color.b, color.a});
    }

    void endDrawing()
    {
        EndDrawing();
    }
}