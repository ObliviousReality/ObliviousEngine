#pragma once

#include "ObliviousEngine/Core/Input.h"

namespace OE
{
    class WinInput : public Input
    {
    protected:
        virtual bool isKeyPressedImp(KeyCode KC) override;
        virtual bool isMousePressedImp(MouseCode button) override;
        virtual float getMouseXImp() override;
        virtual float getMouseYImp() override;
        virtual std::pair<float, float> getMousePosImp() override;
    };
} // namespace OE
