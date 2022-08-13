#pragma once
#include "Core.h"
#include "ObliviousEngine/Entities/ObjectList.h"
#include <SDL.h>
#include "ObliviousEngine/Core/EventHandler.h"

namespace OE {

	class OBLIVIOUSENGINE_API Scene {
	public:
		Scene(SDL_Renderer* renderer, EventHandler* handler);
		~Scene();
		void update();

	private:
		ObjectList::ObjectNode* entities;
	};

}