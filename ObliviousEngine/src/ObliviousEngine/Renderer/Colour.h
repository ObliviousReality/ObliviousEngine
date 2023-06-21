#pragma once
#ifndef COLOUR_H
#define COLOUR_H

#include "Core.h"
namespace OE {

	class OBLIVIOUSENGINE_API Colour
	{
	public:
		Colour(float r, float g, float b, float a = 1.0f);
		~Colour();
		float getR();
		float getG();
		float getB();
		float getA();
		float r, g, b, a;
	private:
	};

}

#endif // !COLOUR_H
