#pragma once
#include "BoxEntity.h"
#include "Core.h"
#include <ObliviousEngine/Core/InputEvent.h>
#include <ObliviousEngine/Audio/SoundEffect.h>

namespace OE
{
	class OBLIVIOUSENGINE_API MovingBox : public BoxEntity
	{
	public:
		MovingBox(int x, int y, Renderer* renderer, EventHandler* handler);
		~MovingBox();

		void update() override;
		int getCollisionClass() override;

	private:
		void movePosition();
		bool travelling = false;
		EventHandler* handler;
		InputEvent* click;
		SoundEffect* flick;
		int newX = 0;
		int newY = 0;
		int velX = 0;
		int velY = 0;
		int divisor = 150;
		int count = 0;
	};
}