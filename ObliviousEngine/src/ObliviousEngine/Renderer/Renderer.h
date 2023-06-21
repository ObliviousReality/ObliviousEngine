#pragma once

#include "RenderCommand.h"
namespace OE
{

	class Renderer
	{
	public:

		static void BeginScene(); // TODO: Scene Params
		static void EndScene();

		static void Draw(const std::shared_ptr<VertexArray>& vArray);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}