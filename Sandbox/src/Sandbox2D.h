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
};