#pragma once
#include "core.h"

namespace OE {
	/*struct Vec2
	{
		int x;
		int y;
		Vec2(int xin, int yin) : x(xin), y(yin) {}
	};

	struct Vec3
	{
		int x;
		int y;
		int z;
		Vec3(int xin, int yin, int zin) : x(xin), y(yin), z(zin) {}
	};*/
	class Maths
	{
	public:


		static const double pi;
		static const double e;

		static void Init();
		static int RandomIntRange(int lowerBound, int upperBound);
		static double RandomFloatRange(double lowerBound, double upperBound);
		static double SquareRoot(double x);
		static double Dist(int x1, int y1, int x2, int y2);
		static std::pair<double, double>  Midpoint(double x1, double y1, double x2, double y2);
		static double* Quadratic(double a, double b, double c);
		static double RoundtoN(double n, int d);
	};

}

