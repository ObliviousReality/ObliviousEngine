#pragma once
#include "core.h"

namespace OE {
	struct OBLIVIOUSENGINE_API Vec2
	{
		int x;
		int y;
		Vec2(int xin, int yin) : x(xin), y(yin) {}
	};

	struct OBLIVIOUSENGINE_API Vec3
	{
		int x;
		int y;
		int z;
		Vec3(int xin, int yin, int zin) : x(xin), y(yin), z(zin) {}
	};
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

