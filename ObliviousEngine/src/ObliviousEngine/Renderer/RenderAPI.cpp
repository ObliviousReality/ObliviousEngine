#include "oepch.h"

#include "RenderAPI.h"

#include "Platforms/OpenGL/GLRenderAPI.h"

namespace OE
{
    RenderAPI::API RenderAPI::activeAPI = RenderAPI::API::OpenGL;
    Scope<RenderAPI> RenderAPI::Create()
    {
        switch (activeAPI)
        {
            case RenderAPI::API::None:
            {
                CORE_ASSERT(false, "RenderAPI::None IS NOT CURRENTLY SUPPORTED");
                return nullptr;
            }
            case RenderAPI::API::OpenGL: return CreateScope<GLRenderAPI>();
        }
        CORE_ASSERT(false, "UNKNOWN RENDERER API");
        return nullptr;
    }
} // namespace OE
