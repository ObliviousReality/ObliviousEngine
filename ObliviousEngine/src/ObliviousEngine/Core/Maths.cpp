#include "oepch.h"
#include "Maths.h"

const double OE::Maths::pi = atan(1) * 4;
const double OE::Maths::e = 2.71828182845904523536;

void OE::Maths::init()
{
	srand(time(NULL));
}

int OE::Maths::randomIntRange(int lowerBound, int upperBound)
{
	return lowerBound + rand() % (upperBound - lowerBound + 1);
}

double OE::Maths::randomFloatRange(double lowerBound, double upperBound)
{
	double r = ((double)rand()) / (double)RAND_MAX;
	return lowerBound + (r * (upperBound - lowerBound));
}

double OE::Maths::squareRoot(double x)
{
	return sqrt(x);
}

double OE::Maths::dist(int x1, int y1, int x2, int y2)
{
	return sqrt((pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double* OE::Maths::midpoint(int x1, int y1, int x2, int y2)
{
	double* temp = new double[2];
	temp[0] = (x1 + x2) * 2;
	temp[1] = (y1 + y2) * 2;
	return temp;
}


double* OE::Maths::quadratic(double a, double b, double c)
{
	if (!a) {
		OE_CORE_WARN("a value of 0 sent to Quadratic Formula. Null Returned.");
		return nullptr;
	}
	double* temp = new double[2];
	temp[0] = (-b + squareRoot(pow(b, 2) - 4 * a * c)) / (2 * a);
	temp[1] = (-b - squareRoot(pow(b, 2) - 4 * a * c)) / (2 * a);
	return temp;
}

double OE::Maths::roundtoN(double n, int d)
{
	return round(n * pow(10, d)) / pow(10, d);
}
