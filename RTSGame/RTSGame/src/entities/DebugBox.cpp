#include "..\header\DebugBox.h"

DebugBox::DebugBox(int x, int y, SDL_Renderer* renderer) : Entity(x, y, renderer)
{
	texture.loadFromFile("assets/debug.png");
}

DebugBox::~DebugBox()
{
}

void DebugBox::update()
{
	x = x + 1;
	if (x > 2560)
	{
		x = -100;
	}
}
