#include "oepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platforms/OpenGL/GLVertexArray.h"

namespace OE
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new GLVertexArray();
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
}