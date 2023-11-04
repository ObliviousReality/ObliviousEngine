#pragma once

#include "OE.h"

class Sandbox2D : public OE::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void onAttach() override;
	virtual void onDetatch() override;

	void onUpdate(OE::Timestep ts) override;
	void onImGuiRender() override;
	void onEvent(OE::Event& e) override;
private:
	OE::OrthographicCameraController cameraController;

	OE::Ref<OE::Shader> shader;
	OE::Ref<OE::VertexArray> vertexArr;

	glm::vec4 squareColour = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 square2Colour = { 0.8f, 0.3f, 0.2f, 1.0f };
	glm::vec3 backgroundColour = { 0.2f, 0.2f, 0.2f };

	OE::Ref<OE::Texture2D> testTexture;

	float leftSquareAngle = 0.0f;
	float rightSquareAngle = 0.0f;
	float centerSquareAngle = 0.0f;




};