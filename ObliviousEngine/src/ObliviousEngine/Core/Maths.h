#pragma once
#include "core.h"
#include "math.h"

namespace OE {
#define _USE_MATH_DEFINES
	class OBLIVIOUSENGINE_API Maths
	{
	public:
		static void init();
		static int randomIntRange(int lowerBound, int upperBound);
		static float randomFloatRange(float lowerBound, float upperBound);
		static float squareRoot(float x);
		static float dist(int x1, int y1, int x2, int y2);
		static const double pi;
	};

}

