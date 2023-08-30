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
	void Renderer::Draw(const std::shared_ptr<GLShader>& shader, const std::shared_ptr<VertexArray>& vArray) {
		shader->bind();
		shader->uploadUniformMat4("u_ViewProj", params->ViewProjMatrix);

		vArray->bind();
		RenderCommand::DrawIndexed(vArray);
	}
}