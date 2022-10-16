#pragma once
#include "Core.h"
//#include "ObliviousEngine/Entities/ObjectList.h"
//#include <SDL.h>
#include "entt.hpp"

//#include <ObliviousEngine/Entities/DebugBox.h>

namespace OE {
	class Entity;
	class OBLIVIOUSENGINE_API Scene {
	public:
		Scene(); // 
		~Scene();
		void update();
		Entity createEntity(const std::string& name = std::string());

		//entt::registry& Reg() { return registry; }

	private:
		entt::registry registry;

		friend class Entity;
	};

}