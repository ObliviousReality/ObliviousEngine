#include "oepch.h"
#include "CircleEntity.h"
#include <ObliviousEngine/Core/Maths.h>

namespace OE {

	OE::CircleEntity::CircleEntity(int x, int y, int r, Renderer* renderer) : Entity(x, y, renderer)
	{
		this->r = r;
	}

	OE::CircleEntity::~CircleEntity()
	{
	}

	void OE::CircleEntity::setRadius(int r)
	{
		this->r = r;
	}

	int OE::CircleEntity::getRadius(int r)
	{
		return r;
	}

	double OE::CircleEntity::getArea()
	{
		return Maths::pi * pow(r, 2);
	}

	double OE::CircleEntity::getCircumference()
	{
		return Maths::pi * r * 2;
	}

}