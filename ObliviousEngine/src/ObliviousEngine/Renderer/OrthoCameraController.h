#pragma once
#include "ObliviousEngine/Renderer/OrthoCamera.h"
#include "ObliviousEngine/Core/Timestep.h"

#include "ObliviousEngine/Events/Event.h"
#include "ObliviousEngine/Events/AppEvent.h"
#include "ObliviousEngine/Events/MouseEvent.h"


namespace OE {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float ratio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthographicCamera& getCamera() { return camera; }
		const OrthographicCamera& getCamera() const { return camera; }

		float getZoomLevel() const { return zoom; }
		void setZoomLevel(float newLevel) { zoom = newLevel; }
	private:
		bool onMouseScroll(MouseScrollEvent& mse);
		bool onWindowResize(WindowResizeEvent& rse);
	private:
		float aspectRatio;
		float zoom = 1.0f;
		OrthographicCamera camera;

		bool rotate;

		float cameraRot = 0.0f;
		glm::vec3 cameraPos = { 0.0f,0.0f ,0.0f };
		float cameraSpeed = 5.0f;
		float rotSpeed = 180.0f;
	};
}

