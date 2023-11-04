#include "oepch.h"
#include "ObliviousEngine/Renderer/RenderCommand.h"

namespace OE
{
	Scope<RenderAPI> RenderCommand::rAPI = RenderAPI::Create();
}