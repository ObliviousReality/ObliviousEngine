#include "oepch.h"
#include "DebugBox.h"

namespace OE {

	DebugBox::DebugBox(int x, int y, SDL_Renderer* renderer, EventHandler* handler) : Entity(x, y, renderer)
	{
		texture.loadFromFile("assets/debug.png");
		k = new KeyInput(handler);
		k->addKeyPress(KEY_G);
	}

	DebugBox::~DebugBox()
	{
	}

	void DebugBox::update()
	{
		if (k->testEvent()) {
			y = y + 100;
		}
		x = x + 1;
		if (x > 2560)
		{
			x = -100;
		}
	}

}