#include <Input/Input.hpp>

#include <raylib.h>

namespace Aloha
{
    bool isKeyPressed(KeyboardKey key)
    {
        return IsKeyPressed(key);
    }

    bool isKeyDown(KeyboardKey key)
    {
        return IsKeyDown(key);
    }

    KeyboardKey getKeyPressed()
    {
        return static_cast<KeyboardKey>(GetKeyPressed());
    }

    bool isGamepadButtonPressed(GamepadButton key)
    {
        return IsGamepadButtonPressed(0, key);
    }

    bool isGamepadButtonDown(GamepadButton key)
    {
        return IsGamepadButtonDown(0, key);
    }

    GamepadButton getGamepadButtonPressed()
    {
        return static_cast<GamepadButton>(GetGamepadButtonPressed());
    }
}