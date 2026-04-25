#pragma once
#include <utils.hpp>

namespace Aloha {
    void init(int screenWidth, int screenHeight, const char* title);
    void setFPS(int fps);
    void close();
    bool shouldClose();

    void beginDrawing(Color color);
    void endDrawing();

    void drawText(const char* text, int posX, int posY, int fontSize, Color color);
    void drawRectangle(int x, int y, int width, int height, Color color);
    void drawCircle(int centerX, int centerY, int radius, Color color);

    bool isKeyPressed(KeyboardKey key);
    bool isKeyDown(KeyboardKey key);
    KeyboardKey getKeyPressed();

    bool isGamepadButtonPressed(GamepadButton key);
    bool isGamepadButtonDown(GamepadButton key);
    GamepadButton getGamepadButtonPressed();
}