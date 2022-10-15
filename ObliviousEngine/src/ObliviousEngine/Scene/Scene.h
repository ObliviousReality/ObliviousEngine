#pragma once
#include "Core.h"
#include "ObliviousEngine/Entities/ObjectList.h"
#include <SDL.h>
#include "ObliviousEngine/Core/EventHandler.h"
#include "entt.hpp"
#include <ObliviousEngine/Scene/Components.h>
#include <ObliviousEngine/Entities/DebugBox.h>

namespace OE {

	class OBLIVIOUSENGINE_API Scene {
	public:
		Scene(Renderer* renderer, EventHandler* handler); // 
		~Scene();
		void update();
		entt::entity createEntity();

		entt::registry& Reg() { return registry; }

	private:
		entt::registry registry;
		Renderer* renderer;
		EventHandler* handler;
	};

}