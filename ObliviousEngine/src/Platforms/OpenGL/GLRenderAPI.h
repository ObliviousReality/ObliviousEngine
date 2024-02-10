#pragma once
#include "ObliviousEngine/Renderer/RenderAPI.h"

namespace OE
{
    class GLRenderAPI : public RenderAPI
    {
    public:
        virtual void Init() override;
        virtual void clear() override;
        virtual void setClearColour(const Colour & colour) override;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;

        virtual void drawIndexed(const Ref<VertexArray> & arr) override;
    };
} // namespace OE
