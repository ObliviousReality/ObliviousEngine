#pragma once

#include "ObliviousEngine/Renderer/RenderAPI.h"

namespace OE
{
    class RenderCommand
    {
    public:
        inline static void Init() { rAPI->Init(); }

        inline static void Clear() { rAPI->clear(); }
        inline static void SetClearColour(const Colour & colour) { rAPI->setClearColour(colour); }

        inline static void DrawIndexed(const Ref<VertexArray> & arr) { rAPI->drawIndexed(arr); }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
        {
            rAPI->setViewport(x, y, w, h);
        }

    private:
        static Scope<RenderAPI> rAPI;
    };
} // namespace OE
