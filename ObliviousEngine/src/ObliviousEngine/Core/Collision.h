#pragma once
#include <ObliviousEngine/Entities/BoxEntity.h>
#include <ObliviousEngine/Entities/CircleEntity.h>

namespace OE {

	class OBLIVIOUSENGINE_API Collision 
	{
	public:
		static bool collisionTest(BoxEntity* a, BoxEntity* b);
		static bool collisionTest(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
		static bool collisionTest(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, bool aabb);
		static bool collisionTest(CircleEntity* a, CircleEntity* b);
		static bool collisionTest(BoxEntity* a, CircleEntity* b);
		static bool collisionTest(CircleEntity* a, BoxEntity* b);
		static bool collisionTest(Entity* a, Entity* b);
		static bool collisionTest(Object* a, Object* b);
	};

}