#pragma once
#include <Core.h>
//#include <OE.h>

#include <ObliviousEngine/Core/Maths.h>


namespace OE {

	struct OBLIVIOUSENGINE_API TransformComponent
	{
		/*Vec2 pos;
		Vec2 rot;
		Vec2 sc;*/
		int x;
		int y;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		//TransformComponent(const Vec2& _pos, const Vec2& _rot, const Vec2& _sc) : pos(_pos), rot(_rot), sc(_sc) {}
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