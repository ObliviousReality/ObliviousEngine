#include "oepch.h"
#include "ObliviousEngine/Renderer/Renderer.h"
#include "ObliviousEngine/Renderer/Renderer2D.h"

namespace OE
{

	Scope<Renderer::SceneParams> Renderer::params = CreateScope<Renderer::SceneParams>();

	void Renderer::Init()
	{
		OE_PROFILE_FUNCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Finish()
	{
		Renderer2D::Finish();
	}

	void Renderer::WindowResize(uint32_t w, uint32_t h)
	{
		RenderCommand::SetViewport(0, 0, w, h);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		params->ViewProjMatrix = camera.getViewProjMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Draw(const Ref<Shader>& shader, const Ref<VertexArray>& vArray, const glm::mat4& transform) {
		shader->bind();

		shader->setMat4("u_ViewProj", params->ViewProjMatrix);
		shader->setMat4("transform", transform);


		vArray->bind();
		RenderCommand::DrawIndexed(vArray);
	}
}