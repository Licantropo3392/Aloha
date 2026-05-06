#pragma once

#include <Renderer/Color.hpp>

namespace Aloha
{
    void drawText(const char *text, int posX, int posY, int fontSize, Color color);
    void drawRectangle(int x, int y, int width, int height, Color color);
    void drawCircle(int centerX, int centerY, int radius, Color color);
}