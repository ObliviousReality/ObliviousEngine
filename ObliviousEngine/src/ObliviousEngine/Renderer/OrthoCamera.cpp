#include "oepch.h"
#include "OrthoCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace OE {

	OrthographicCamera::OrthographicCamera(float l, float r, float b, float t) : projMatrix(glm::ortho(l, r, b, t, -1.0f, 1.0f)), viewMatrix(1.0f)
	{
		viewProjMatrix = projMatrix * viewMatrix;
	}

	void OrthographicCamera::setProj(float l, float r, float b, float t)
	{
		projMatrix = glm::ortho(l, r, b, t, -1.0f, 1.0f);
		viewProjMatrix = projMatrix * viewMatrix;
	}

	void OrthographicCamera::recalcVM()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0, 0, 1));
		viewMatrix = glm::inverse(transform);
		viewProjMatrix = projMatrix * viewMatrix;
	}

}