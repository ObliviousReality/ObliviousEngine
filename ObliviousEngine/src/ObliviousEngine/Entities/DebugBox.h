#pragma once
#include "Entity.h"
#include "Core.h"
#include <ObliviousEngine/Core/KeyInput.h>

namespace OE {

	class DebugBox : public Entity
	{
	public:
		DebugBox(int x, int y, SDL_Renderer* renderer, EventHandler* handler);
		~DebugBox();

		void update() override;
	private:
		KeyInput* k;
	};

}