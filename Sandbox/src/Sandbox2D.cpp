#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/ext/matrix_transform.hpp>

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

	OE::RenderCommand::SetClearColour(backgroundColour);
	OE::RenderCommand::Clear();

	OE::Renderer2D::BeginScene(cameraController.getCamera());
	{
		OE::Renderer2D::DrawRect({ -1.0f,0.0f }, { 1.0f,1.5f }, squareColour);
		OE::Renderer2D::DrawRect({ 1.0f,0.0f }, { 1.5f,1.0f }, square2Colour);

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
	ImGui::ColorEdit4("Square2 Colour", glm::value_ptr(square2Colour));
	ImGui::ColorEdit3("Background Colour", glm::value_ptr(backgroundColour));

	ImGui::End();
}

void Sandbox2D::onEvent(OE::Event& e)
{
	cameraController.onEvent(e);
}
