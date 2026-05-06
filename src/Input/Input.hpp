#pragma once

#include <Input/KeyboardEnum.hpp>
#include <Input/GamepadEnum.hpp>

namespace Aloha
{
    bool isKeyPressed(KeyboardKey key);
    bool isKeyDown(KeyboardKey key);
    KeyboardKey getKeyPressed();

    bool isGamepadButtonPressed(GamepadButton key);
    bool isGamepadButtonDown(GamepadButton key);
    GamepadButton getGamepadButtonPressed();
}