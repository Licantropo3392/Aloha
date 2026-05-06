#pragma once

namespace Aloha
{
    typedef enum
    {
        GAMEPAD_BUTTON_UNKNOWN = 0,      // Unknown button, just for error checking
        GAMEPAD_BUTTON_LEFT_FACE_UP,     // Gamepad left DPAD up button
        GAMEPAD_BUTTON_LEFT_FACE_RIGHT,  // Gamepad left DPAD right button
        GAMEPAD_BUTTON_LEFT_FACE_DOWN,   // Gamepad left DPAD down button
        GAMEPAD_BUTTON_LEFT_FACE_LEFT,   // Gamepad left DPAD left button
        GAMEPAD_BUTTON_RIGHT_FACE_UP,    // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
        GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, // Gamepad right button right (i.e. PS3: Circle, Xbox: B)
        GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
        GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // Gamepad right button left (i.e. PS3: Square, Xbox: X)
        GAMEPAD_BUTTON_LEFT_TRIGGER_1,   // Gamepad top/back trigger left (first), it could be a trailing button
        GAMEPAD_BUTTON_LEFT_TRIGGER_2,   // Gamepad top/back trigger left (second), it could be a trailing button
        GAMEPAD_BUTTON_RIGHT_TRIGGER_1,  // Gamepad top/back trigger right (first), it could be a trailing button
        GAMEPAD_BUTTON_RIGHT_TRIGGER_2,  // Gamepad top/back trigger right (second), it could be a trailing button
        GAMEPAD_BUTTON_MIDDLE_LEFT,      // Gamepad center buttons, left one (i.e. PS3: Select)
        GAMEPAD_BUTTON_MIDDLE,           // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
        GAMEPAD_BUTTON_MIDDLE_RIGHT,     // Gamepad center buttons, right one (i.e. PS3: Start)
        GAMEPAD_BUTTON_LEFT_THUMB,       // Gamepad joystick pressed button left
        GAMEPAD_BUTTON_RIGHT_THUMB       // Gamepad joystick pressed button right
    } GamepadButton;
}