#pragma once
#include <Core.h>
//#include <OE.h>

#include <ObliviousEngine/Core/Maths.h>


namespace OE {

	struct TagComponent
	{
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& text) : tag(text) {}
	};

	struct OBLIVIOUSENGINE_API TransformComponent
	{
		//Vec2 pos;
		int x;
		int y;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		//TransformComponent(Vec2 _pos) : pos(_pos){}
		TransformComponent(const int _x, const int _y) : x(_x), y(_y) {}
	};

	struct OBLIVIOUSENGINE_API SpriteRendererComponent
	{
		Vec3 colour{ 255,255,255 };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Vec3& col) : colour(col) {}
	};
}