#pragma once

#include "ObliviousEngine/Core/Input.h"

#include "ObliviousEngine/Events/Event.h"

namespace OE
{
    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(float x, float y) : mouseX((int)x), mouseY((int)y) {}

        inline float getX() const { return (float)mouseX; }
        inline float getY() const { return (float)mouseY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse Move Event: " << mouseX << ", " << mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMove);
        EVENT_CLASS_CAT(ECMouse | ECInput);

    private:
        int mouseX, mouseY;
    };

    class MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(float x, float y) : xOff(x), yOff(y) {}

        inline float getXOff() const { return xOff; }
        inline float getYOff() const { return yOff; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse Scroll Event: " << xOff << ", " << yOff;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScroll);
        EVENT_CLASS_CAT(ECMouse | ECInput);

    private:
        float xOff, yOff;
    };

    class MouseButtonEvent : public Event
    {
    public:
        inline MouseCode getButton() const { return button; }

        EVENT_CLASS_CAT(ECMouse | ECInput);

    protected:
        MouseButtonEvent(MouseCode but) : button(but) {}
        MouseCode button;
    };

    class MouseDownEvent : public MouseButtonEvent
    {
    public:
        MouseDownEvent(MouseCode but) : MouseButtonEvent(but) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse Down: " << button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseDown);
    };

    class MouseUpEvent : public MouseButtonEvent
    {
    public:
        MouseUpEvent(MouseCode but) : MouseButtonEvent(but) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse Up: " << button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseUp);
    };
} // namespace OE
