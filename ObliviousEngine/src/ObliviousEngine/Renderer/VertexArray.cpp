#include "oepch.h"

#include "Renderer.h"
#include "VertexArray.h"

#include "Platforms/OpenGL/GLVertexArray.h"

namespace OE
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RenderAPI::API::None:
            {
                OE_CORE_ASSERT(false, "RenderAPI::None IS NOT CURRENTLY SUPPORTED");
                return nullptr;
            }
            case RenderAPI::API::OpenGL:
            {
                return CreateRef<GLVertexArray>();
            }
            default:
            {
                OE_CORE_ASSERT(false, "UNKOWN RENDERER API");
                return nullptr;
            }
        }
    }
} // namespace OE
