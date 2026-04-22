#include <platform.hpp>
#include <raylib.h>

namespace Aloha {
    void init(int screenWidth, int screenHeight, const char* title) {
        InitWindow(screenWidth, screenHeight, title);
    }

    void setFPS(int fps) {
        SetTargetFPS(fps);
    }

    void close() {
        CloseWindow();
    }

    bool shouldClose() {
        return WindowShouldClose();
    }

    void beginDrawing(Color color) {
        BeginDrawing();
        ClearBackground({color.r, color.g, color.b, color.a});
    }

    void endDrawing() {
        EndDrawing();
    }

    void drawRectangle(int x, int y, int width, int height, Color color) {
        DrawRectangle(x, y, width, height, {color.r, color.g, color.b, color.a});
    }

    void drawCircle(int centerX, int centerY, int radius, Color color) {
        DrawCircle(centerX, centerY, radius, {color.r, color.g, color.b, color.a});
    }
}