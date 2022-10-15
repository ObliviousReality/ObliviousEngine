#include "oepch.h"
#include "Collision.h"

bool OE::Collision::collisionTest(BoxEntity* a, BoxEntity* b)
{
	OE_CORE_INFO("BE, BE");
	return collisionTest(a->getX(), a->getY(), a->getWidth(), a->getHeight(), b->getX(), b->getY(), b->getWidth(), b->getHeight());
}

bool OE::Collision::collisionTest(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	OE_CORE_INFO("XYWH");
	OE_CORE_TRACE(x1);
	OE_CORE_TRACE(y1);
	OE_CORE_TRACE(w1);
	OE_CORE_TRACE(h1);
	OE_CORE_TRACE(x2);
	OE_CORE_TRACE(y2);
	OE_CORE_TRACE(w2);
	OE_CORE_TRACE(h2);
	if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2) {
		return true;
	}
	return false;
}

bool OE::Collision::collisionTest(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, bool aabb)
{
	OE_CORE_INFO("AABB");
	return false;
}

bool OE::Collision::collisionTest(CircleEntity* a, CircleEntity* b)
{
	OE_CORE_INFO("CE, CE");
	return false;
}

bool OE::Collision::collisionTest(BoxEntity* a, CircleEntity* b)
{
	OE_CORE_INFO("BE, CE");
	return false;
}

bool OE::Collision::collisionTest(CircleEntity* a, BoxEntity* b)
{
	OE_CORE_INFO("CE, BE");
	return collisionTest(b, a);
}

bool OE::Collision::collisionTest(OldEntity* a, OldEntity* b)
{
	OE_CORE_ERROR("Collision object specified which does not have a shape type. Please make sure your classes involved with collision do not extend Entity. False returned.");
	return false;
}

bool OE::Collision::collisionTest(Object* a, Object* b)
{
	OE_CORE_ERROR("Collision object specified which does not have a shape type. Please make sure your classes involved with collision do not extend Object. False returned.");
	return false;
}
