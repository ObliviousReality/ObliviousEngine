#include "oepch.h"
#include "Maths.h"

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
