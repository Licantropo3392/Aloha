#include <Input/Input.hpp>

#include <3ds.h>

namespace Aloha
{
    bool isKeyPressed(KeyboardKey key)
    {
        return false; // Not working on 3DS
    }

    bool isKeyDown(KeyboardKey key)
    {
        return false; // Not working on 3DS
    }

    KeyboardKey getKeyPressed()
    {
        return KEYBOARD_NULL; // Not working on 3DS
    }

    bool isGamepadButtonPressed(GamepadButton key)
    {
        u32 kDown = hidKeysDown();
        if (key == GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)
            return (kDown & KEY_A) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_FACE_DOWN)
            return (kDown & KEY_B) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_FACE_LEFT)
            return (kDown & KEY_X) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_FACE_UP)
            return (kDown & KEY_Y) != 0;
        if (key == GAMEPAD_BUTTON_LEFT_TRIGGER_1)
            return (kDown & KEY_L) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_TRIGGER_1)
            return (kDown & KEY_R) != 0;
        if (key == GAMEPAD_BUTTON_LEFT_TRIGGER_2)
            return (kDown & KEY_ZL) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_TRIGGER_2)
            return (kDown & KEY_ZR) != 0;
        if (key == GAMEPAD_BUTTON_MIDDLE_RIGHT)
            return (kDown & KEY_START) != 0;
        if (key == GAMEPAD_BUTTON_MIDDLE_LEFT)
            return (kDown & KEY_SELECT) != 0;
        return false;
    }

    bool isGamepadButtonDown(GamepadButton key)
    {
        u32 kDown = hidKeysHeld();
        if (key == GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)
            return (kDown & KEY_A) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_FACE_DOWN)
            return (kDown & KEY_B) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_FACE_LEFT)
            return (kDown & KEY_X) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_FACE_UP)
            return (kDown & KEY_Y) != 0;
        if (key == GAMEPAD_BUTTON_LEFT_TRIGGER_1)
            return (kDown & KEY_L) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_TRIGGER_1)
            return (kDown & KEY_R) != 0;
        if (key == GAMEPAD_BUTTON_LEFT_TRIGGER_2)
            return (kDown & KEY_ZL) != 0;
        if (key == GAMEPAD_BUTTON_RIGHT_TRIGGER_2)
            return (kDown & KEY_ZR) != 0;
        if (key == GAMEPAD_BUTTON_MIDDLE_RIGHT)
            return (kDown & KEY_START) != 0;
        if (key == GAMEPAD_BUTTON_MIDDLE_LEFT)
            return (kDown & KEY_SELECT) != 0;
        return false;
    }

    GamepadButton getGamepadButtonPressed()
    {
        u32 kDown = hidKeysDown();
        if (kDown & KEY_A)
            return GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
        if (kDown & KEY_B)
            return GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
        if (kDown & KEY_X)
            return GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
        if (kDown & KEY_Y)
            return GAMEPAD_BUTTON_RIGHT_FACE_UP;
        if (kDown & KEY_L)
            return GAMEPAD_BUTTON_LEFT_TRIGGER_1;
        if (kDown & KEY_R)
            return GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
        if (kDown & KEY_ZL)
            return GAMEPAD_BUTTON_LEFT_TRIGGER_2;
        if (kDown & KEY_ZR)
            return GAMEPAD_BUTTON_RIGHT_TRIGGER_2;
        if (kDown & KEY_START)
            return GAMEPAD_BUTTON_MIDDLE_RIGHT;
        if (kDown & KEY_SELECT)
            return GAMEPAD_BUTTON_MIDDLE_LEFT;
        return GAMEPAD_BUTTON_UNKNOWN; // No key pressed
    }
}