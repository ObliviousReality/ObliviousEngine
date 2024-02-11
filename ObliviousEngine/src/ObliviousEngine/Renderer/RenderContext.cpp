#include "oepch.h"

#include "RenderContext.h"
#include "Renderer.h"

#include "Platforms/OpenGL/OpenGLContext.h"

namespace OE
{
    Scope<RenderContext> RenderContext::Create(void * window)
    {
        switch (Renderer::GetAPI())
        {
            case RenderAPI::API::None:
                OE_CORE_ASSERT(false, "RenderAPI::None IS NOT CURRENTLY SUPPORTED");
                return nullptr;
            case RenderAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
        }
        OE_CORE_ASSERT(false, "UNKNOWN RENDERER API");
        return nullptr;
    }

} // namespace OE
