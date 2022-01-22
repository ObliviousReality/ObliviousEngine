#include "..\header\Object.h"
//#include "Object.h"

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
