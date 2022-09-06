#include "oepch.h"
#include "MovingBox.h"
#include <ObliviousEngine/Audio/MediaPlayer.h>
#include <ObliviousEngine/Core/Maths.h>

namespace OE
{
	MovingBox::MovingBox(int x, int y, Renderer* renderer, EventHandler* handler) : BoxEntity(x, y, 0, 0, renderer)
	{
		setWidth(100);
		setHeight(100);
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
		newX = x;
		newY = y;
		do
		{
			newX = Maths::randomIntRange(10, 1800);
			newY = Maths::randomIntRange(10, 900);
		} while (Maths::dist(x, y, newX, newY) < 25);
		velX = (newX - x) / divisor;
		velY = (newY - y) / divisor;
	}
}