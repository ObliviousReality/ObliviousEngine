#pragma once

namespace OE
{
    typedef enum class KeyCode :
        uint16_t
    {
        // From glfw3.h
        Space = 32,
        Apostrophe = 39, /* ' */
        Comma = 44,      /* , */
        Minus = 45,      /* - */
        Period = 46,     /* . */
        Slash = 47,      /* / */

        D0 = 48, /* 0 */
        D1 = 49, /* 1 */
        D2 = 50, /* 2 */
        D3 = 51, /* 3 */
        D4 = 52, /* 4 */
        D5 = 53, /* 5 */
        D6 = 54, /* 6 */
        D7 = 55, /* 7 */
        D8 = 56, /* 8 */
        D9 = 57, /* 9 */

        Semicolon = 59, /* ; */
        Equals = 61,    /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LBracket = 91,  /* [ */
        Backslash = 92, /* \ */
        RBracket = 93,  /* ] */
        Grave = 96,     /* ` */

        World1 = 161, /* non-US #1 */
        World2 = 162, /* non-US #2 */

        /* Function keys */
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        /* Keypad */
        NUM_0 = 320,
        NUM_1 = 321,
        NUM_2 = 322,
        NUM_3 = 323,
        NUM_4 = 324,
        NUM_5 = 325,
        NUM_6 = 326,
        NUM_7 = 327,
        NUM_8 = 328,
        NUM_9 = 329,
        NUM_Decimal = 330,
        NUM_Divide = 331,
        NUM_Multiply = 332,
        NUM_Subtract = 333,
        NUM_Add = 334,
        NUM_Enter = 335,
        NUM_Equals = 336,

        LShift = 340,
        LControl = 341,
        LAlt = 342,
        LWin = 343,
        RShift = 344,
        RControl = 345,
        RAlt = 346,
        RWin = 347,
        Menu = 348
    } Key;

    inline std::ostream & operator<<(std::ostream & os, KeyCode keyCode)
    {
        os << static_cast<int32_t>(keyCode);
        return os;
    }
} // namespace OE

// From glfw3.h
#define KEY_SPACE      ::OE::Key::Space
#define KEY_APOSTROPHE ::OE::Key::Apostrophe /* ' */
#define KEY_COMMA      ::OE::Key::Comma      /* , */
#define KEY_MINUS      ::OE::Key::Minus      /* - */
#define KEY_PERIOD     ::OE::Key::Period     /* . */
#define KEY_SLASH      ::OE::Key::Slash      /* / */
#define KEY_0          ::OE::Key::D0
#define KEY_1          ::OE::Key::D1
#define KEY_2          ::OE::Key::D2
#define KEY_3          ::OE::Key::D3
#define KEY_4          ::OE::Key::D4
#define KEY_5          ::OE::Key::D5
#define KEY_6          ::OE::Key::D6
#define KEY_7          ::OE::Key::D7
#define KEY_8          ::OE::Key::D8
#define KEY_9          ::OE::Key::D9
#define KEY_SEMICOLON  ::OE::Key::Semicolon /* ; */
#define KEY_EQUALS     ::OE::Key::Equals    /* = */
#define KEY_A          ::OE::Key::A
#define KEY_B          ::OE::Key::B
#define KEY_C          ::OE::Key::C
#define KEY_D          ::OE::Key::D
#define KEY_E          ::OE::Key::E
#define KEY_F          ::OE::Key::F
#define KEY_G          ::OE::Key::G
#define KEY_H          ::OE::Key::H
#define KEY_I          ::OE::Key::I
#define KEY_J          ::OE::Key::J
#define KEY_K          ::OE::Key::K
#define KEY_L          ::OE::Key::L
#define KEY_M          ::OE::Key::M
#define KEY_N          ::OE::Key::N
#define KEY_O          ::OE::Key::O
#define KEY_P          ::OE::Key::P
#define KEY_Q          ::OE::Key::Q
#define KEY_R          ::OE::Key::R
#define KEY_S          ::OE::Key::S
#define KEY_T          ::OE::Key::T
#define KEY_U          ::OE::Key::U
#define KEY_V          ::OE::Key::V
#define KEY_W          ::OE::Key::W
#define KEY_X          ::OE::Key::X
#define KEY_Y          ::OE::Key::Y
#define KEY_Z          ::OE::Key::Z
#define KEY_LBRACKET   ::OE::Key::LBracket  /* [ */
#define KEY_BACKSLASH  ::OE::Key::Backslash /* \ */
#define KEY_RBRACKET   ::OE::Key::RBracket  /* ] */
#define KEY_GRAVE      ::OE::Key::Grave     /* ` */
#define KEY_WORLD_1    ::OE::Key::World1    /* non-US #1 */
#define KEY_WORLD_2    ::OE::Key::World2    /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE       ::OE::Key::Escape
#define KEY_ENTER        ::OE::Key::Enter
#define KEY_TAB          ::OE::Key::Tab
#define KEY_BACKSPACE    ::OE::Key::Backspace
#define KEY_INSERT       ::OE::Key::Insert
#define KEY_DELETE       ::OE::Key::Delete
#define KEY_RIGHT        ::OE::Key::Right
#define KEY_LEFT         ::OE::Key::Left
#define KEY_DOWN         ::OE::Key::Down
#define KEY_UP           ::OE::Key::Up
#define KEY_PAGE_UP      ::OE::Key::PageUp
#define KEY_PAGE_DOWN    ::OE::Key::PageDown
#define KEY_HOME         ::OE::Key::Home
#define KEY_END          ::OE::Key::End
#define KEY_CAPS_LOCK    ::OE::Key::CapsLock
#define KEY_SCROLL_LOCK  ::OE::Key::ScrollLock
#define KEY_NUM_LOCK     ::OE::Key::NumLock
#define KEY_PRINT_SCREEN ::OE::Key::PrintScreen
#define KEY_PAUSE        ::OE::Key::Pause
#define KEY_F1           ::OE::Key::F1
#define KEY_F2           ::OE::Key::F2
#define KEY_F3           ::OE::Key::F3
#define KEY_F4           ::OE::Key::F4
#define KEY_F5           ::OE::Key::F5
#define KEY_F6           ::OE::Key::F6
#define KEY_F7           ::OE::Key::F7
#define KEY_F8           ::OE::Key::F8
#define KEY_F9           ::OE::Key::F9
#define KEY_F10          ::OE::Key::F10
#define KEY_F11          ::OE::Key::F11
#define KEY_F12          ::OE::Key::F12
#define KEY_F13          ::OE::Key::F13
#define KEY_F14          ::OE::Key::F14
#define KEY_F15          ::OE::Key::F15
#define KEY_F16          ::OE::Key::F16
#define KEY_F17          ::OE::Key::F17
#define KEY_F18          ::OE::Key::F18
#define KEY_F19          ::OE::Key::F19
#define KEY_F20          ::OE::Key::F20
#define KEY_F21          ::OE::Key::F21
#define KEY_F22          ::OE::Key::F22
#define KEY_F23          ::OE::Key::F23
#define KEY_F24          ::OE::Key::F24
#define KEY_F25          ::OE::Key::F25

/* Keypad */
#define KEY_NUM_0        ::OE::Key::NUM_0
#define KEY_NUM_1        ::OE::Key::NUM_1
#define KEY_NUM_2        ::OE::Key::NUM_2
#define KEY_NUM_3        ::OE::Key::NUM_3
#define KEY_NUM_4        ::OE::Key::NUM_4
#define KEY_NUM_5        ::OE::Key::NUM_5
#define KEY_NUM_6        ::OE::Key::NUM_6
#define KEY_NUM_7        ::OE::Key::NUM_7
#define KEY_NUM_8        ::OE::Key::NUM_8
#define KEY_NUM_9        ::OE::Key::NUM_9
#define KEY_NUM_DECIMAL  ::OE::Key::NUM_Decimal
#define KEY_NUM_DIVIDE   ::OE::Key::NUM_Divide
#define KEY_NUM_MULTIPLY ::OE::Key::NUM_Multiply
#define KEY_NUM_SUBTRACT ::OE::Key::NUM_Subtract
#define KEY_NUM_ADD      ::OE::Key::NUM_Add
#define KEY_NUM_ENTER    ::OE::Key::NUM_Enter
#define KEY_NUM_EQUALS   ::OE::Key::NUM_Equals

#define KEY_LSHIFT   ::OE::Key::LShift
#define KEY_LCONTROL ::OE::Key::LControl
#define KEY_LALT     ::OE::Key::LAlt
#define KEY_LWIN     ::OE::Key::LWin
#define KEY_RSHIFT   ::OE::Key::RShift
#define KEY_RCONTROL ::OE::Key::RControl
#define KEY_RALT     ::OE::Key::RAlt
#define KEY_RWIN     ::OE::Key::RWin
#define KEY_MENU     ::OE::Key::Menu