#pragma once
#include "core.h"

namespace OE {

	class OBLIVIOUSENGINE_API Maths
	{
	public:
		static const double pi;
		static const double e;

		static void init();
		static int randomIntRange(int lowerBound, int upperBound);
		static double randomFloatRange(double lowerBound, double upperBound);
		static double squareRoot(double x);
		static double dist(int x1, int y1, int x2, int y2);
		static double* midpoint(int x1, int y1, int x2, int y2);
		static double* quadratic(double a, double b, double c);
		static double roundtoN(double n, int d);
	};

}

