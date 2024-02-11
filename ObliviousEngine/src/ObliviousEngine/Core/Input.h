#pragma once

#include "Core.h"

#include "ObliviousEngine/Events/KeyCodes.h"
#include "ObliviousEngine/Events/MouseCodes.h"

namespace OE
{
    class Input
    {
    public:
        inline static bool isKeyPressed(KeyCode keyCode) { return instance->isKeyPressedImp(keyCode); }
        inline static bool isMousePressed(MouseCode button) { return instance->isMousePressedImp(button); }
        inline static float getMouseX() { return instance->getMouseXImp(); }
        inline static float getMouseY() { return instance->getMouseYImp(); }
        inline static std::pair<float, float> GetMousePos() { return instance->getMousePosImp(); }

        static Scope<Input> Create();
    protected:
        virtual bool isKeyPressedImp(KeyCode keyCode) = 0;
        virtual bool isMousePressedImp(MouseCode button) = 0;
        virtual float getMouseXImp() = 0;
        virtual float getMouseYImp() = 0;
        virtual std::pair<float, float> getMousePosImp() = 0;

    private:
        static Scope<Input> instance;
    };
} // namespace OE
