#pragma once

#include <Renderer/Color.hpp>

namespace Aloha::WindowImpl
{
    void create(int screenWidth, int screenHeight, const char *title);
    void setFPS(int fps);
    void close();
    bool shouldClose();

    void beginDrawing(Color color);
    void endDrawing();
}