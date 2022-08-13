#pragma once
#include "Entity.h"
#include "Core.h"
#include <ObliviousEngine/Core/InputEvent.h>

namespace OE {

	class OBLIVIOUSENGINE_API DebugBox : public Entity
	{
	public:
		DebugBox(int x, int y, SDL_Renderer* renderer, EventHandler* handler);
		~DebugBox();

		void update() override;
	private:
		InputEvent* k;
	};

}