#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include <Platforms/OpenGL/GLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f)
{

}

void Sandbox2D::onAttach()
{
	vertexArr = OE::VertexArray::Create();

	float square[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	OE::Ref<OE::VertexBuffer> vertexBuf;
	vertexBuf.reset(OE::VertexBuffer::Create(square, sizeof(square)));

	OE::BufferLayout layout = {
		{OE::ShaderType::Float3, "position"}
	};

	vertexBuf->setLayout(layout);
	vertexArr->addVertexBuffer(vertexBuf);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

	OE::Ref<OE::IndexBuffer> indexBuf;
	indexBuf.reset(OE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	vertexArr->setIndexBuffer(indexBuf);

	shader = OE::Shader::Create("assets/shaders/Flat.glsl");
}

void Sandbox2D::onDetatch()
{
}

void Sandbox2D::onUpdate(OE::Timestep ts)
{
	cameraController.onUpdate(ts);

	OE::RenderCommand::SetClearColour({ 0.2f,0.2f ,0.2f });
	OE::RenderCommand::Clear();

	std::dynamic_pointer_cast<OE::GLShader>(shader)->bind();
	std::dynamic_pointer_cast<OE::GLShader>(shader)->uploadUniformFloat4("u_Colour", squareColour);

	OE::Renderer::BeginScene(cameraController.getCamera());
	{
		OE::Renderer::Draw(shader, vertexArr, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	}
	OE::Renderer::EndScene();

	if (OE::Input::isKeyPressed(KEY_P)) {
		OE_TRACE("P PRESSED");
		OE::Application::Quit();
	}
}

void Sandbox2D::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Colour", glm::value_ptr(squareColour));
	ImGui::End();
}

void Sandbox2D::onEvent(OE::Event& e)
{
	cameraController.onEvent(e);
}
