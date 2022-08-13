#include "oepch.h"
#include "DebugBox.h"
#include <ObliviousEngine/Audio/MediaPlayer.h>

namespace OE {

	DebugBox::DebugBox(int x, int y, SDL_Renderer* renderer, EventHandler* handler) : Entity(x, y, renderer)
	{
		this->handler = handler;
		this->w = 100;
		this->h = 100;
		texture.loadFromFile("assets/debug.png");
		flick = new SoundEffect("assets/flick.mp3");
		left = new InputEvent(handler);
		right = new InputEvent(handler);
		up = new InputEvent(handler);
		down = new InputEvent(handler);
		reset = new InputEvent(handler);
		click = new InputEvent(handler);
		left->addKeyPress(KEY_LEFT);
		left->addKeyPress(KEY_A);
		right->addKeyPress(KEY_RIGHT);
		right->addKeyPress(KEY_D);
		up->addKeyPress(KEY_UP);
		up->addKeyPress(KEY_W);
		down->addKeyPress(KEY_DOWN);
		down->addKeyPress(KEY_S);
		reset->addKeyPress(KEY_R);
		click->addMouseClick(LEFTMOUSE);
	}

	DebugBox::~DebugBox()
	{
	}

	void DebugBox::update()
	{
		if (left->testEvent()) {
			x = x - 5;
		}
		if (right->testEvent()) {
			x = x + 5;
		}
		if (up->testEvent()) {
			y = y - 5;
		}
		if (down->testEvent()) {
			y = y + 5;
		}
		if (reset->testEvent()) {
			x = 50;
			y = 50;
		}
		if (click->testEvent()) {
			int* pos = handler->getMouseXY();
			OE_CORE_WARN("Mouse Coords: {} X and {} Y.", pos[0], pos[1]);
			OE_CORE_WARN("Box Coords: {} X and {} Y.", x, y);
			if (pos[0] > x && pos[0] < x + w) {
				if (pos[1] > y && pos[1] < y + h) {
					MediaPlayer::playEffect(flick);
				}
			}
		}
	}

}