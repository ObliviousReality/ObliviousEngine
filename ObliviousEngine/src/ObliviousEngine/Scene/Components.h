#pragma once
#include <Core.h>
// #include <OE.h>

#include <ObliviousEngine/Core/Maths.h>
#include <ObliviousEngine/Renderer/Camera.h>

namespace OE
{

    struct TagComponent
    {
        std::string tag;

        TagComponent() = default;
        TagComponent(const TagComponent &) = default;
        TagComponent(const std::string & text) : tag(text) {}
    };

    struct TransformComponent
    {
        // Vec2 pos;
        glm::vec2 vec;

        TransformComponent() = default;
        TransformComponent(const TransformComponent &) = default;
        // TransformComponent(Vec2 _pos) : pos(_pos){}
        TransformComponent(const glm::vec2 & _v) : vec(_v) {} // const int _x, const int _y, x(_x), y(_y),
    };

    struct SpriteRendererComponent
    {
        // Texture* tex;
        int i;

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent &) = default;
        // SpriteRendererComponent(Texture* t) : tex(t) {}
        SpriteRendererComponent(const int & t) : i(t) {}
    };

    struct CameraComponent
    {
        Camera camera;
        bool primary = false;

        CameraComponent() = default;
        CameraComponent(const CameraComponent &) = default;
        CameraComponent(const glm::mat4 & _camera) : camera(_camera) {}
    };
} // namespace OE
