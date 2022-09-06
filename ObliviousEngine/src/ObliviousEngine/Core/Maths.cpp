#include "oepch.h"
#include "Maths.h"

const double OE::Maths::pi = 3.14;

void OE::Maths::init()
{
	srand(time(NULL));
	
}

int OE::Maths::randomIntRange(int lowerBound, int upperBound)
{
	return lowerBound + rand() % (upperBound - lowerBound + 1);
}

float OE::Maths::randomFloatRange(float lowerBound, float upperBound)
{
	float r = ((float)rand()) / (float)RAND_MAX;
	return lowerBound + (r * (upperBound - lowerBound));
}

float OE::Maths::squareRoot(float x)
{
	return sqrt(x);
}

float OE::Maths::dist(int x1, int y1, int x2, int y2)
{
	return sqrt((pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
