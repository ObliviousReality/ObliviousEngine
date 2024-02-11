#pragma once

#include "ObliviousEngine/Core/Input.h"

#include "ObliviousEngine/Events/Event.h"

namespace OE
{
    class KeyEvent : public Event
    {
    public:
        inline KeyCode getKeyCode() const { return keyCode; }

        EVENT_CLASS_CAT(ECKeyboard | ECInput);

    protected:
        KeyEvent(KeyCode kc) : keyCode(kc) {}

        KeyCode keyCode;
    };

    class KeyDownEvent : public KeyEvent
    {
    public:
        KeyDownEvent(KeyCode kc, int repCount) : KeyEvent(kc), repeatCount(repCount) {}

        inline int getRepCount() const { return repeatCount; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyDownEvent: " << keyCode << " (" << repeatCount << " times).";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyDown);

    private:
        int repeatCount;
    };

    class KeyUpEvent : public KeyEvent
    {
    public:
        KeyUpEvent(KeyCode kc) : KeyEvent(kc) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyUpEvent: " << keyCode;
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyUp);
    };

    class KeyTypeEvent : public KeyEvent
    {
    public:
        KeyTypeEvent(KeyCode kc) : KeyEvent(kc) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyTypeEvent: " << keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyType);
    };
} // namespace OE
