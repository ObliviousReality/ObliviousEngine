#pragma once

#include <glm/glm.hpp>

namespace OE {
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float l, float r, float b, float t);
		void setProj(float l, float r, float b, float t);

		void setPos(const glm::vec3& p) { pos = p; recalcVM(); }
		void setRot(float r) { rot = r; recalcVM(); }

		const glm::vec3 getPos() const { return pos; }
		float getRot() const { return rot; }

		const glm::mat4 getProjMatrix() const { return projMatrix; }
		const glm::mat4 getViewMatrix() const { return viewMatrix; }
		const glm::mat4 getViewProjMatrix() const { return viewProjMatrix; }

	private:
		void recalcVM();

	private:
		glm::mat4 projMatrix;
		glm::mat4 viewMatrix;

		glm::mat4 viewProjMatrix;

		glm::vec3 pos = { 0.0f,0.0f,0.0f };
		float rot = 0.0f;
	};
}