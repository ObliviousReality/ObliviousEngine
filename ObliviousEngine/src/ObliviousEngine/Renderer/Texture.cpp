#include "oepch.h"

#include "Core.h"

#include "Renderer.h"
#include "Texture.h"

#include "Platforms/OpenGL/GLTexture.h"

namespace OE
{
    Ref<Texture2D> Texture2D::Create(const std::string & p)
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
                return CreateRef<GLTexture2D>(p);
            }
            default:
            {
                OE_CORE_ASSERT(false, "UNKOWN RENDERER API");
                return nullptr;
            }
        }
    }
    Ref<Texture2D> Texture2D::Create(uint32_t w, uint32_t h)
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
                return CreateRef<GLTexture2D>(w, h);
            }
            default:
            {
                OE_CORE_ASSERT(false, "UNKOWN RENDERER API");
                return nullptr;
            }
        }
    }
} // namespace OE
