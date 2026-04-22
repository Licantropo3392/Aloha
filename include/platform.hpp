#pragma once

namespace Aloha {
    typedef struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } Color;

    void init(int screenWidth, int screenHeight, const char* title);
    void setFPS(int fps);
    void close();
    bool shouldClose();

    void beginDrawing(Color color);
    void endDrawing();

    void drawRectangle(int x, int y, int width, int height, Color color);
    void drawCircle(int centerX, int centerY, int radius, Color color);
}