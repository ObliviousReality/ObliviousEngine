#include "oepch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Platforms/OpenGL/GLShader.h"
#include "RenderCommand.h"

namespace OE
{

	struct R2DStorage
	{
		Ref<VertexArray> vArray;
		Ref<Shader> shader;
	};

	static R2DStorage* storage;

	void Renderer2D::Init()
	{
		storage = new R2DStorage();
		storage->vArray = VertexArray::Create();

		float square[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> vertexBuf;
		vertexBuf.reset(VertexBuffer::Create(square, sizeof(square)));

		BufferLayout layout = {
			{ShaderType::Float3, "position"}
		};

		vertexBuf->setLayout(layout);
		storage->vArray->addVertexBuffer(vertexBuf);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		Ref<IndexBuffer> indexBuf;
		indexBuf.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		storage->vArray->setIndexBuffer(indexBuf);

		storage->shader = Shader::Create("assets/shaders/Flat.glsl");
	}
	void Renderer2D::Finish()
	{
		delete storage;
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<GLShader>(storage->shader)->bind();
		std::dynamic_pointer_cast<GLShader>(storage->shader)->uploadUniformMat4("u_ViewProj", camera.getViewProjMatrix());
		std::dynamic_pointer_cast<GLShader>(storage->shader)->uploadUniformMat4("transform", glm::mat4(1.0f));


	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& colour)
	{
		DrawRect({ pos.x, pos.y, 0.0f }, size, colour);
	}
	void Renderer2D::DrawRect(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& colour)
	{
		std::dynamic_pointer_cast<GLShader>(storage->shader)->bind();
		std::dynamic_pointer_cast<GLShader>(storage->shader)->uploadUniformFloat4("u_Colour", colour);

		storage->vArray->bind();
		RenderCommand::DrawIndexed(storage->vArray);
	}
}