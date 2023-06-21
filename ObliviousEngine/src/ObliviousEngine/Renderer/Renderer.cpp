#include "oepch.h"
#include "Renderer.h"

namespace OE
{
	void Renderer::BeginScene()
	{
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Draw(const std::shared_ptr<VertexArray>& vArray)
	{
		vArray->bind();
		RenderCommand::DrawIndexed(vArray);
	}
}