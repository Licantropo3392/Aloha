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

    void beginDrawing() {
        BeginDrawing();
    }

    void clearBackground(Color color) {
        ClearBackground(color);
    }

    void endDrawing() {
        EndDrawing();
    }

    void drawRectangle(int x, int y, int width, int height, Color color) {
        DrawRectangle(x, y, width, height, color);
    }

    void drawCircle(int centerX, int centerY, int radius, Color color) {
        DrawCircle(centerX, centerY, radius, color);
    }
}