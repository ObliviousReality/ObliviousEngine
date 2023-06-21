#include "oepch.h"
#include "Colour.h"

namespace OE {

	Colour::Colour(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Colour::~Colour()
	{
	}

	float Colour::getR()
	{
		return r;
	}

	float Colour::getG()
	{
		return g;
	}

	float Colour::getB()
	{
		return b;
	}

	float Colour::getA()
	{
		return a;
	}
}