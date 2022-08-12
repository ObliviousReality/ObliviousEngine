#pragma once
#ifndef COLOUR_H
#define COLOUR_H

#include "Core.h"
namespace OE {

	class OBLIVIOUSENGINE_API Colour
	{
	public:
		Colour(int r, int g, int b, int a = 255);
		~Colour();
		int getR();
		int getG();
		int getB();
		int getA();
	private:
		int r, g, b, a;
	};

}

#endif // !COLOUR_H
