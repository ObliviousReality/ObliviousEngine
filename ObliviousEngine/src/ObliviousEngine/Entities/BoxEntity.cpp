#include "oepch.h"
#include "BoxEntity.h"

namespace OE
{
	BoxEntity::BoxEntity(int x, int y, int w, int h, Renderer* renderer) : Entity(x, y, renderer)
	{
		this->w = w;
		this->h = h;
	}
	BoxEntity::~BoxEntity()
	{
	}
	void BoxEntity::setDimensions(int w, int h)
	{
		this->w = w;
		this->h = h;
	}
	void BoxEntity::setHeight(int h)
	{
		this->h = h;
	}
	void BoxEntity::setWidth(int w)
	{
		this->w = w;
	}

	int* BoxEntity::getDimesions()
	{
		int* temp = new int[2];
		temp[0] = w;
		temp[1] = h;
		return temp;
	}
	int BoxEntity::getHeight()
	{
		return h;
	}
	int BoxEntity::getWidth()
	{
		return w;
	}

	double BoxEntity::getArea()
	{
		return w * h;
	}
	double BoxEntity::getCircumference()
	{
		return (2 * w) + (2 * h);
	}
}
