#include "oepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platforms/OpenGL/GLShader.h"

namespace OE
{
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new GLShader(vertexSource, fragmentSource);
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
}