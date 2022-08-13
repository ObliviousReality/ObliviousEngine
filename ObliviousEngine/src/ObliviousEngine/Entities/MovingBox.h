#pragma once
#include "Entity.h"
#include "Core.h"
#include <ObliviousEngine/Core/InputEvent.h>
#include <ObliviousEngine/Audio/SoundEffect.h>

namespace OE
{
	class OBLIVIOUSENGINE_API MovingBox : public Entity
	{
	public:
		MovingBox(int x, int y, SDL_Renderer* renderer, EventHandler* handler);
		~MovingBox();

		void update() override;

	private:
		void movePosition();
		bool travelling = false;
		EventHandler* handler;
		InputEvent* click;
		SoundEffect* flick;
		int newX, newY = 0;
		int velX, velY = 0;
		int divisor = 150;
		int count = 0;
	};
}