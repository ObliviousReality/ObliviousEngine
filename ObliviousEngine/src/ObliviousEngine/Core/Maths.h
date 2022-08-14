#pragma once
#include "core.h"

namespace OE {

	class OBLIVIOUSENGINE_API Maths
	{
	public:
		static void init();
		static int randomIntRange(int lowerBound, int upperBound);
		static float randomFloatRange(float lowerBound, float upperBound);
		static float squareRoot(float x);
	};

}

