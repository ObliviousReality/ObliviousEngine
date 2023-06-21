#include "oepch.h"
#include "RenderCommand.h"

#include "Platforms/OpenGL/GLRenderAPI.h"

namespace OE
{
	RenderAPI* RenderCommand::rAPI = new GLRenderAPI;
}