#pragma once
#include "BoxEntity.h"
#include "Core.h"
#include <ObliviousEngine/Core/InputEvent.h>
#include <ObliviousEngine/Audio/SoundEffect.h>

namespace OE {

	class OBLIVIOUSENGINE_API DebugBox : public BoxEntity
	{
	public:
		DebugBox(int x, int y, Renderer* renderer, EventHandler* handler);
		~DebugBox();

		void update() override;
		void onCollide(Entity* e) override;
		int getCollisionClass() override;
	private:
		EventHandler* handler;
		InputEvent* left; 
		InputEvent* right; 
		InputEvent* up; 
		InputEvent* down;
		InputEvent* reset;
		InputEvent* click;
		SoundEffect* flick;
	};

}