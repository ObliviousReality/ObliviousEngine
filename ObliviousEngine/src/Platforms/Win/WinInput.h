#pragma once

#include "ObliviousEngine/Core/Input.h"

namespace OE
{
    class WinInput : public Input
    {
    protected:
        virtual bool isKeyPressedImp(int KC) override;
        virtual bool isMousePressedImp(int button) override;
        virtual float getMouseXImp() override;
        virtual float getMouseYImp() override;
        virtual std::pair<float, float> getMousePosImp() override;
    };
} // namespace OE
