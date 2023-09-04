#include "oepch.h"
#include "Texture.h"

#include <string>
#include "Core.h"

#include "Renderer.h"

#include "Platforms/OpenGL/GLTexture.h"

namespace OE {

	Ref<Texture2D> Texture2D::Create(const std::string& p)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<GLTexture2D>(p);
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
}
