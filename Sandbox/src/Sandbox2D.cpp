#include "Sandbox2D.h"

#include <glm/glm/ext/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f, true) {}

void Sandbox2D::onAttach()
{
    PROFILE_FUNCTION();
    testTexture = OE::Texture2D::Create("assets/textures/OE mk3.png");
}

void Sandbox2D::onDetatch()
{
    PROFILE_FUNCTION();
}

void Sandbox2D::onUpdate(OE::Timestep ts)
{
    PROFILE_FUNCTION();

    cameraController.onUpdate(ts);
    {
        PROFILE_SCOPE("RenderReset");
        OE::RenderCommand::SetClearColour(backgroundColour);
        OE::RenderCommand::Clear();
    }

    {
        PROFILE_SCOPE("RenderDraw");
        OE::Renderer2D::BeginScene(cameraController.getCamera());
        {
            OE::Renderer2D::DrawRotatedRect({ -1.0f, 0.0f }, { 1.0f, 1.5f }, leftSquareAngle, squareColour);
            OE::Renderer2D::DrawRotatedRect({ 1.0f, 0.0f }, { 1.5f, 1.0f }, rightSquareAngle, square2Colour);
            OE::Renderer2D::DrawRotatedRect(
                { 0.0f, 0.0f, -0.1f },
                { 10.5f, 10.5f },
                centerSquareAngle,
                testTexture,
                1.0f,
                centerSquareTint);
        }
    }
    OE::Renderer2D::EndScene();

    if (OE::Input::isKeyPressed(KEY_P) || buttonPressed)
    {
        TRACE("P PRESSED");
        OE::Application::Quit();
    }
}

void Sandbox2D::onImGuiRender()
{
    PROFILE_FUNCTION();
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
}

void Sandbox2D::onEvent(OE::Event & e)
{
    cameraController.onEvent(e);
}
