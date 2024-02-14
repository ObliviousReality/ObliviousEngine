#pragma once

#include "OrthoCamera.h"
#include "Texture.h"

namespace OE
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Finish();

        static void BeginScene(const OrthographicCamera & camera);
        static void EndScene();

        static void DrawRect(const glm::vec2 & pos, const glm::vec2 & size, const glm::vec4 & colour);
        static void DrawRect(const glm::vec3 & pos, const glm::vec2 & size, const glm::vec4 & colour);

        static void DrawRect(
            const glm::vec2 & pos, // TODO: Change these from params into a struct with default vals
            const glm::vec2 & size,
            const Ref<Texture2D> & texture,
            float tilingFactor = 1.0f,
            const glm::vec4 & tint = glm::vec4(1.0f));
        static void DrawRect(
            const glm::vec3 & pos,
            const glm::vec2 & size,
            const Ref<Texture2D> & texture,
            float tilingFactor = 1.0f,
            const glm::vec4 & tint = glm::vec4(1.0f));

        static void DrawRotatedRect(
            const glm::vec2 & pos,
            const glm::vec2 & size,
            float rotation,
            const glm::vec4 & colour);
        static void DrawRotatedRect(
            const glm::vec3 & pos,
            float rotation,
            const glm::vec2 & size,
            const glm::vec4 & colour);

        static void DrawRotatedRect(
            const glm::vec2 & pos, // TODO: Change these from params into a struct with default vals
            const glm::vec2 & size,
            float rotation,
            const Ref<Texture2D> & texture,
            float tilingFactor = 1.0f,
            const glm::vec4 & tint = glm::vec4(1.0f));
        static void DrawRotatedRect(
            const glm::vec3 & pos,
            const glm::vec2 & size,
            float rotation,
            const Ref<Texture2D> & texture,
            float tilingFactor = 1.0f,
            const glm::vec4 & tint = glm::vec4(1.0f));
    };
} // namespace OE
