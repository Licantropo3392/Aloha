#include <Renderer/platform.hpp>

#include <raylib.h>

namespace Aloha
{
    void drawText(const char *text, int posX, int posY, int fontSize, Color color)
    {
        DrawText(text, posX, posY, fontSize, {color.r, color.g, color.b, color.a});
        // DrawTextEx();
    }

    void drawRectangle(int x, int y, int width, int height, Color color)
    {
        DrawRectangle(x, y, width, height, {color.r, color.g, color.b, color.a});
    }

    void drawCircle(int centerX, int centerY, int radius, Color color)
    {
        DrawCircle(centerX, centerY, radius, {color.r, color.g, color.b, color.a});
    }
}