#include "oepch.h"
#include "ObliviousEngine/Renderer/RenderContext.h"

#include "ObliviousEngine/Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLContext.h"

namespace OE {

	Scope<RenderContext> RenderContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RenderAPI::None is not currently supported");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		OE_CORE_ASSERT(false, "ERROR: Unkown RenderAPI");
		return nullptr;
	}

}