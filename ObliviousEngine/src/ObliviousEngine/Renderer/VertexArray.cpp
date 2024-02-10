#include "ObliviousEngine/Renderer/Renderer.h"
#include "ObliviousEngine/Renderer/VertexArray.h"
#include "Platforms/OpenGL/GLVertexArray.h"
#include "oepch.h"

namespace OE
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RenderAPI::API::None: OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateRef<GLVertexArray>();
            default: OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET"); return nullptr;
        }
    }
} // namespace OE
