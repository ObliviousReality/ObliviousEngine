#include "oepch.h"
#include "Renderer.h"

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
	void Renderer::Draw(const std::shared_ptr<GLShader>& shader, const std::shared_ptr<VertexArray>& vArray, const glm::mat4& transform) {
		shader->bind();
		shader->uploadUniformMat4("u_ViewProj", params->ViewProjMatrix);
		shader->uploadUniformMat4("transform", transform);

		vArray->bind();
		RenderCommand::DrawIndexed(vArray);
	}
}