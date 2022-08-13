#include "oepch.h"
#include "MovingBox.h"
#include <ObliviousEngine/Audio/MediaPlayer.h>

namespace OE
{
	MovingBox::MovingBox(int x, int y, SDL_Renderer* renderer, EventHandler* handler) : Entity(x, y, renderer)
	{
		this->w = 100;
		this->h = 100;
		this->handler = handler;
		texture.loadFromFile("assets/debug.png");
		click = new InputEvent(handler);
		click->addMouseClick(LEFTMOUSE);
		flick = new SoundEffect("assets/flick.mp3");

	}
	MovingBox::~MovingBox()
	{
	}
	void MovingBox::update()
	{
		if (travelling) {
			x = x + velX;
			y = y + velY;
			count++;
			if (count == divisor) {
				travelling = false;
				count = 0;
			}
		}
		else if (click->testEvent())
		{
			int* pos = handler->getMouseXY();
			if (pos[0] > x && pos[0] < x + w) {
				if (pos[1] > y && pos[1] < y + h) {
					MediaPlayer::playEffect(flick);
					movePosition();
					travelling = true;
				}
			}
		}
	}
	void MovingBox::movePosition()
	{
		newX = 10 + (std::rand() % (1800 - 10 + 1));
		newY = 10 + (std::rand() % (900 - 10 + 1));
		velX = (newX - x) / divisor;
		velY = (newY - y) / divisor;
	}
}