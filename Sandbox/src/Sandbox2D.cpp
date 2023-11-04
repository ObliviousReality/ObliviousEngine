#include "Sandbox2D.h"
#include <imgui/imgui.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* n, Fn&& funcy)
		: name(n), stopped(false), func(funcy)
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		if (!stopped)
			stop();
	}

	void stop() {
		auto endTime = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

		stopped = true;

		float d = (end - start) * 0.001f;

		//std::cout << name << ": " << d << "ms" << std::endl;
		func({ name, d });

	}

private:
	const char* name;
	std::chrono::time_point<std::chrono::steady_clock> startTime;
	bool stopped;
	Fn func;

};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfilerResult profileResult) { results.push_back(profileResult); })

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f, true)
{
}

void Sandbox2D::onAttach()
{
	testTexture = OE::Texture2D::Create("assets/textures/Logo2023.png");
}

void Sandbox2D::onDetatch()
{
}

void Sandbox2D::onUpdate(OE::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::onUpdate");

	{
		PROFILE_SCOPE("Camera::onUpdate");
		cameraController.onUpdate(ts);
	}
	{
		PROFILE_SCOPE("RenderReset");
		OE::RenderCommand::SetClearColour(backgroundColour);
		OE::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("RenderDraw");
		OE::Renderer2D::BeginScene(cameraController.getCamera());
		{
			OE::Renderer2D::DrawRect({ -1.0f, 0.0f }, { 1.0f, 1.5f }, squareColour, leftSquareAngle);
			OE::Renderer2D::DrawRect({ 1.0f, 0.0f }, { 1.5f, 1.0f }, square2Colour, rightSquareAngle);
			OE::Renderer2D::DrawRect({ 0.0f, 0.0f, -0.1f }, { 10.5f, 10.5f }, testTexture, centerSquareAngle, centerSquareTint);
		}
	}
	OE::Renderer2D::EndScene();

	if (OE::Input::isKeyPressed(KEY_P) || buttonPressed) {
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
	ImGui::ColorEdit4("Center Square Tint", glm::value_ptr(centerSquareTint));
	ImGui::SliderFloat("Left Box Angle", &leftSquareAngle, 0.0f, 360.0f);
	ImGui::SliderFloat("Right Box Angle", &rightSquareAngle, 0.0f, 360.0f);
	ImGui::SliderFloat("Center Box Angle", &centerSquareAngle, 0.0f, 360.0f);
	buttonPressed = ImGui::Button("Quit");
	ImGui::End();

	ImGui::Begin("Profiler");
	for (auto& result : results) {
		char label[50];
		strcpy(label, "% .3fms  ");
		strcat(label, result.name);
		ImGui::Text(label, result.t);
	}
	results.clear();
	ImGui::End();
}

void Sandbox2D::onEvent(OE::Event& e)
{
	cameraController.onEvent(e);
}
