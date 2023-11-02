#include "oepch.h"
#include "Renderer.h"
#include <Platforms/OpenGL/GLShader.h>
#include "Renderer2D.h"

namespace OE
{

	Renderer::SceneParams* Renderer::params = new Renderer::SceneParams;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
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
		std::dynamic_pointer_cast<GLShader>(shader)->uploadUniformMat4("u_ViewProj", params->ViewProjMatrix);
		std::dynamic_pointer_cast<GLShader>(shader)->uploadUniformMat4("transform", transform);

		vArray->bind();
		RenderCommand::DrawIndexed(vArray);
	}
}