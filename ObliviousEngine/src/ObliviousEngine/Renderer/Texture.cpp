#include "oepch.h"

#include "Core.h"
#include "ObliviousEngine/Renderer/Renderer.h"
#include "ObliviousEngine/Renderer/Texture.h"
#include "Platforms/OpenGL/GLTexture.h"

#include <string>

namespace OE
{

    Ref<Texture2D> Texture2D::Create(const std::string & p)
    {
        switch (Renderer::GetAPI())
        {
            case RenderAPI::API::None: OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED"); return nullptr;
            case RenderAPI::API::OpenGL: return std::make_shared<GLTexture2D>(p);
            default: OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET"); return nullptr;
        }
    }
    Ref<Texture2D> Texture2D::Create(uint32_t w, uint32_t h)
    {
        switch (Renderer::GetAPI())
        {
            case RenderAPI::API::None: OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED"); return nullptr;
            case RenderAPI::API::OpenGL: return std::make_shared<GLTexture2D>(w, h);
            default: OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET"); return nullptr;
        }
    }
} // namespace OE
