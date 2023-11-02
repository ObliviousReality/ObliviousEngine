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
	
}

void Sandbox2D::onDetatch()
{
}

void Sandbox2D::onUpdate(OE::Timestep ts)
{
	cameraController.onUpdate(ts);

	OE::RenderCommand::SetClearColour({ 0.2f,0.2f ,0.2f });
	OE::RenderCommand::Clear();

	OE::Renderer2D::BeginScene(cameraController.getCamera());
	{
		OE::Renderer2D::DrawRect({ 0.0f,0.0f }, { 1.0f,1.0f }, squareColour);
	}
	OE::Renderer2D::EndScene();

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
