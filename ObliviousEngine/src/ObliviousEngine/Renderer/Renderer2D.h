#pragma once

#include "ObliviousEngine/Renderer/OrthoCamera.h"
#include "ObliviousEngine/Renderer/Texture.h"

namespace OE
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Finish();

        static void BeginScene(const OrthographicCamera & camera);
        static void EndScene();

        static void DrawRect(const glm::vec2 & pos, const glm::vec2 & size, const glm::vec4 & colour, float a = 0.0f);
        static void DrawRect(const glm::vec3 & pos, const glm::vec2 & size, const glm::vec4 & colour, float a = 0.0f);

        static void DrawRect(const glm::vec2 & pos,
                             const glm::vec2 & size,
                             const Ref<Texture2D> & texture,
                             float a = 0.0f,
                             const glm::vec4 & colour = glm::vec4(1.0f));
        static void DrawRect(const glm::vec3 & pos,
                             const glm::vec2 & size,
                             const Ref<Texture2D> & texture,
                             float a = 0.0f,
                             const glm::vec4 & colour = glm::vec4(1.0f));
    };
} // namespace OE
