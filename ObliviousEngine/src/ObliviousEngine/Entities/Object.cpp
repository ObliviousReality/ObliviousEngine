#include "oepch.h"
#include "Object.h"

namespace OE {

	Object::Object()
	{
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
	}

	Object::~Object()
	{
	}

	void Object::draw()
	{
	}

	void Object::update()
	{
	}

	void Object::onCollide(Object* e)
	{
		OE_CORE_ERROR("Wrong collide function");
	}

	int Object::getX()
	{
		return x;
	}

	int Object::getY()
	{
		return y;
	}

	int Object::getWidth()
	{
		return w;
	}

	int Object::getHeight()
	{
		return h;
	}

	int Object::getCollisionClass()
	{
		return 0;
	}

}