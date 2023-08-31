#include "oepch.h"
#include "Renderer.h"
#include <Platforms/OpenGL/GLShader.h>

namespace OE
{

	Renderer::SceneParams* Renderer::params = new Renderer::SceneParams;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		params->ViewProjMatrix = camera.getViewProjMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Draw(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vArray, const glm::mat4& transform) {
		shader->bind();
		std::dynamic_pointer_cast<GLShader>(shader)->uploadUniformMat4("u_ViewProj", params->ViewProjMatrix);
		std::dynamic_pointer_cast<GLShader>(shader)->uploadUniformMat4("transform", transform);

		vArray->bind();
		RenderCommand::DrawIndexed(vArray);
	}
}