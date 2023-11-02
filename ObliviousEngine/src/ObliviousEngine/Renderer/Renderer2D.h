#pragma once

#include "OrthoCamera.h"

namespace OE {
	class Renderer2D
	{
	public:
		static void Init();
		static void Finish();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& colour);
		static void DrawRect(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& colour);

	};
}