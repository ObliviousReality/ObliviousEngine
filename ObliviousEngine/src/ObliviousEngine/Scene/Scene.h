#pragma once
#include "Core.h"
#include "entt.hpp"


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