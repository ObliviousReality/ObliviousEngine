#pragma once
#include "Colour.h"
#include "ObliviousEngine/Renderer/VertexArray.h"
namespace OE
{
    class RenderAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1
        };

    public:
        virtual void Init() = 0;
        virtual void clear() = 0;
        virtual void setClearColour(const Colour & colour) = 0;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;

        virtual void drawIndexed(const Ref<VertexArray> & arr) = 0;

        inline static API GetAPI() { return activeAPI; }

        static Scope<RenderAPI> Create();

    private:
        static API activeAPI;
    };
} // namespace OE
