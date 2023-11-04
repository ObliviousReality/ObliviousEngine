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
			OE_CORE_ASSERT(false, "RenderAPI::None is not currently supported");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return CreateScope<GLRenderAPI>();
		}
		OE_CORE_ASSERT(false, "ERROR: Unkown RenderAPI!");
		return nullptr;
	}
}