#pragma once

namespace Aloha {
    typedef struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } Color;

    typedef enum {
        KEYBOARD_NULL            = 0,        // Key: NULL, used for no key pressed
        // Alphanumeric keys
        KEYBOARD_APOSTROPHE      = 39,       // Key: '
        KEYBOARD_COMMA           = 44,       // Key: ,
        KEYBOARD_MINUS           = 45,       // Key: -
        KEYBOARD_PERIOD          = 46,       // Key: .
        KEYBOARD_SLASH           = 47,       // Key: /
        KEYBOARD_ZERO            = 48,       // Key: 0
        KEYBOARD_ONE             = 49,       // Key: 1
        KEYBOARD_TWO             = 50,       // Key: 2
        KEYBOARD_THREE           = 51,       // Key: 3
        KEYBOARD_FOUR            = 52,       // Key: 4
        KEYBOARD_FIVE            = 53,       // Key: 5
        KEYBOARD_SIX             = 54,       // Key: 6
        KEYBOARD_SEVEN           = 55,       // Key: 7
        KEYBOARD_EIGHT           = 56,       // Key: 8
        KEYBOARD_NINE            = 57,       // Key: 9
        KEYBOARD_SEMICOLON       = 59,       // Key: ;
        KEYBOARD_EQUAL           = 61,       // Key: =
        KEYBOARD_A               = 65,       // Key: A | a
        KEYBOARD_B               = 66,       // Key: B | b
        KEYBOARD_C               = 67,       // Key: C | c
        KEYBOARD_D               = 68,       // Key: D | d
        KEYBOARD_E               = 69,       // Key: E | e
        KEYBOARD_F               = 70,       // Key: F | f
        KEYBOARD_G               = 71,       // Key: G | g
        KEYBOARD_H               = 72,       // Key: H | h
        KEYBOARD_I               = 73,       // Key: I | i
        KEYBOARD_J               = 74,       // Key: J | j
        KEYBOARD_K               = 75,       // Key: K | k
        KEYBOARD_L               = 76,       // Key: L | l
        KEYBOARD_M               = 77,       // Key: M | m
        KEYBOARD_N               = 78,       // Key: N | n
        KEYBOARD_O               = 79,       // Key: O | o
        KEYBOARD_P               = 80,       // Key: P | p
        KEYBOARD_Q               = 81,       // Key: Q | q
        KEYBOARD_R               = 82,       // Key: R | r
        KEYBOARD_S               = 83,       // Key: S | s
        KEYBOARD_T               = 84,       // Key: T | t
        KEYBOARD_U               = 85,       // Key: U | u
        KEYBOARD_V               = 86,       // Key: V | v
        KEYBOARD_W               = 87,       // Key: W | w
        KEYBOARD_X               = 88,       // Key: X | x
        KEYBOARD_Y               = 89,       // Key: Y | y
        KEYBOARD_Z               = 90,       // Key: Z | z
        KEYBOARD_LEFT_BRACKET    = 91,       // Key: [
        KEYBOARD_BACKSLASH       = 92,       // Key: '\'
        KEYBOARD_RIGHT_BRACKET   = 93,       // Key: ]
        KEYBOARD_GRAVE           = 96,       // Key: `
        // Function keys
        KEYBOARD_SPACE           = 32,       // Key: Space
        KEYBOARD_ESCAPE          = 256,      // Key: Esc
        KEYBOARD_ENTER           = 257,      // Key: Enter
        KEYBOARD_TAB             = 258,      // Key: Tab
        KEYBOARD_BACKSPACE       = 259,      // Key: Backspace
        KEYBOARD_INSERT          = 260,      // Key: Ins
        KEYBOARD_DELETE          = 261,      // Key: Del
        KEYBOARD_RIGHT           = 262,      // Key: Cursor right
        KEYBOARD_LEFT            = 263,      // Key: Cursor left
        KEYBOARD_DOWN            = 264,      // Key: Cursor down
        KEYBOARD_UP              = 265,      // Key: Cursor up
        KEYBOARD_PAGE_UP         = 266,      // Key: Page up
        KEYBOARD_PAGE_DOWN       = 267,      // Key: Page down
        KEYBOARD_HOME            = 268,      // Key: Home
        KEYBOARD_END             = 269,      // Key: End
        KEYBOARD_CAPS_LOCK       = 280,      // Key: Caps lock
        KEYBOARD_SCROLL_LOCK     = 281,      // Key: Scroll down
        KEYBOARD_NUM_LOCK        = 282,      // Key: Num lock
        KEYBOARD_PRINT_SCREEN    = 283,      // Key: Print screen
        KEYBOARD_PAUSE           = 284,      // Key: Pause
        KEYBOARD_F1              = 290,      // Key: F1
        KEYBOARD_F2              = 291,      // Key: F2
        KEYBOARD_F3              = 292,      // Key: F3
        KEYBOARD_F4              = 293,      // Key: F4
        KEYBOARD_F5              = 294,      // Key: F5
        KEYBOARD_F6              = 295,      // Key: F6
        KEYBOARD_F7              = 296,      // Key: F7
        KEYBOARD_F8              = 297,      // Key: F8
        KEYBOARD_F9              = 298,      // Key: F9
        KEYBOARD_F10             = 299,      // Key: F10
        KEYBOARD_F11             = 300,      // Key: F11
        KEYBOARD_F12             = 301,      // Key: F12
        KEYBOARD_LEFT_SHIFT      = 340,      // Key: Shift left
        KEYBOARD_LEFT_CONTROL    = 341,      // Key: Control left
        KEYBOARD_LEFT_ALT        = 342,      // Key: Alt left
        KEYBOARD_LEFT_SUPER      = 343,      // Key: Super left
        KEYBOARD_RIGHT_SHIFT     = 344,      // Key: Shift right
        KEYBOARD_RIGHT_CONTROL   = 345,      // Key: Control right
        KEYBOARD_RIGHT_ALT       = 346,      // Key: Alt right
        KEYBOARD_RIGHT_SUPER     = 347,      // Key: Super right
        KEYBOARD_KB_MENU         = 348,      // Key: KB menu
        // Keypad keys
        KEYBOARD_KP_0            = 320,      // Key: Keypad 0
        KEYBOARD_KP_1            = 321,      // Key: Keypad 1
        KEYBOARD_KP_2            = 322,      // Key: Keypad 2
        KEYBOARD_KP_3            = 323,      // Key: Keypad 3
        KEYBOARD_KP_4            = 324,      // Key: Keypad 4
        KEYBOARD_KP_5            = 325,      // Key: Keypad 5
        KEYBOARD_KP_6            = 326,      // Key: Keypad 6
        KEYBOARD_KP_7            = 327,      // Key: Keypad 7
        KEYBOARD_KP_8            = 328,      // Key: Keypad 8
        KEYBOARD_KP_9            = 329,      // Key: Keypad 9
        KEYBOARD_KP_DECIMAL      = 330,      // Key: Keypad .
        KEYBOARD_KP_DIVIDE       = 331,      // Key: Keypad /
        KEYBOARD_KP_MULTIPLY     = 332,      // Key: Keypad *
        KEYBOARD_KP_SUBTRACT     = 333,      // Key: Keypad -
        KEYBOARD_KP_ADD          = 334,      // Key: Keypad +
        KEYBOARD_KP_ENTER        = 335,      // Key: Keypad Enter
        KEYBOARD_KP_EQUAL        = 336,      // Key: Keypad =
        // Android key buttons
        KEYBOARD_BACK            = 4,        // Key: Android back button
        KEYBOARD_MENU            = 5,        // Key: Android menu button
        KEYBOARD_VOLUME_UP       = 24,       // Key: Android volume up button
        KEYBOARD_VOLUME_DOWN     = 25        // Key: Android volume down button
    } KeyboardKey;

    typedef enum {
        GAMEPAD_BUTTON_UNKNOWN = 0,         // Unknown button, just for error checking
        GAMEPAD_BUTTON_LEFT_FACE_UP,        // Gamepad left DPAD up button
        GAMEPAD_BUTTON_LEFT_FACE_RIGHT,     // Gamepad left DPAD right button
        GAMEPAD_BUTTON_LEFT_FACE_DOWN,      // Gamepad left DPAD down button
        GAMEPAD_BUTTON_LEFT_FACE_LEFT,      // Gamepad left DPAD left button
        GAMEPAD_BUTTON_RIGHT_FACE_UP,       // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
        GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,    // Gamepad right button right (i.e. PS3: Circle, Xbox: B)
        GAMEPAD_BUTTON_RIGHT_FACE_DOWN,     // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
        GAMEPAD_BUTTON_RIGHT_FACE_LEFT,     // Gamepad right button left (i.e. PS3: Square, Xbox: X)
        GAMEPAD_BUTTON_LEFT_TRIGGER_1,      // Gamepad top/back trigger left (first), it could be a trailing button
        GAMEPAD_BUTTON_LEFT_TRIGGER_2,      // Gamepad top/back trigger left (second), it could be a trailing button
        GAMEPAD_BUTTON_RIGHT_TRIGGER_1,     // Gamepad top/back trigger right (first), it could be a trailing button
        GAMEPAD_BUTTON_RIGHT_TRIGGER_2,     // Gamepad top/back trigger right (second), it could be a trailing button
        GAMEPAD_BUTTON_MIDDLE_LEFT,         // Gamepad center buttons, left one (i.e. PS3: Select)
        GAMEPAD_BUTTON_MIDDLE,              // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
        GAMEPAD_BUTTON_MIDDLE_RIGHT,        // Gamepad center buttons, right one (i.e. PS3: Start)
        GAMEPAD_BUTTON_LEFT_THUMB,          // Gamepad joystick pressed button left
        GAMEPAD_BUTTON_RIGHT_THUMB          // Gamepad joystick pressed button right
    } GamepadButton;
}