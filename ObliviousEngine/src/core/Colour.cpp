#include "pch.h"
#include "..\header\Colour.h"

Colour::Colour(int r, int g, int b, int a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Colour::~Colour()
{
}

int Colour::getR()
{
	return r;
}

int Colour::getG()
{
	return g;
}

int Colour::getB()
{
	return b;
}

int Colour::getA()
{
	return a;
}
