#pragma once
class Colour
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

