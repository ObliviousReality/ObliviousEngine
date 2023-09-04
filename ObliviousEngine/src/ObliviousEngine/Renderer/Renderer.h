#pragma once

#include "RenderCommand.h"

#include "OrthoCamera.h"
#include "Shader.h"

namespace OE
{

	class Renderer
	{
	public:

		static void BeginScene(OrthographicCamera& camera); // TODO: Scene Params
		static void EndScene();

		static void Draw(const Ref<Shader>& shader, const Ref<VertexArray>& vArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
		struct SceneParams
		{
			glm::mat4 ViewProjMatrix;
		};

		static SceneParams* params;
	};
}