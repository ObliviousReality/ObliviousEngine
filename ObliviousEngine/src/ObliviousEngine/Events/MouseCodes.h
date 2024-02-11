#pragma once

namespace OE
{
    typedef enum class MouseCode :
        uint16_t
    {
        // From glfw3.h
        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,

        ButtonLast = Button7,
        ButtonLeft = Button0,
        ButtonRight = Button1,
        ButtonMiddle = Button2
    } Mouse;

    inline std::ostream & operator<<(std::ostream & os, MouseCode mouseCode)
    {
        os << static_cast<int32_t>(mouseCode);
        return os;
    }
} // namespace OE

#define OE_MOUSE_0      ::OE::Mouse::Button0
#define OE_MOUSE_1      ::OE::Mouse::Button1
#define OE_MOUSE_2      ::OE::Mouse::Button2
#define OE_MOUSE_3      ::OE::Mouse::Button3
#define OE_MOUSE_4      ::OE::Mouse::Button4
#define OE_MOUSE_5      ::OE::Mouse::Button5
#define OE_MOUSE_6      ::OE::Mouse::Button6
#define OE_MOUSE_7      ::OE::Mouse::Button7
#define OE_MOUSE_LAST   ::OE::Mouse::ButtonLast
#define OE_MOUSE_LEFT   ::OE::Mouse::ButtonLeft
#define OE_MOUSE_RIGHT  ::OE::Mouse::ButtonRight
#define OE_MOUSE_MIDDLE ::OE::Mouse::ButtonMiddle