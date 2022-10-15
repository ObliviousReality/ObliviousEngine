#pragma once
#include "Core.h"
#include "Scene.h"
#include "entt.hpp"
#include "ObliviousEngine/Core/Log.h"

namespace OE {

	class OBLIVIOUSENGINE_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity h, Scene* s);
		Entity(const Entity& other) = default;

		template<typename T>
		bool hasComp()
		{
			return scene->registry.all_of<T>(handle);
		}

		template<typename T, typename... Args>
		T& addComp(Args&&... args)
		{
			if (hasComp<T>()) {
				OE_CORE_WARN("Entity already has component!");
			}
			return scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComp()
		{
			if (!hasComp<T>()) {
				OE_CORE_WARN("Entity does not have component!");
			}
			return scene->registry.get<T>(handle);
		}

		template<typename T>
		void remComp()
		{
			if (!hasComp<T>()) {
				OE_CORE_WARN("Entity does not have component!");
			}
			scene->registry.remove<T>(handle);
		}

		operator bool() const { return handle != entt::null; }

	private:
		entt::entity handle = entt::null;
		Scene* scene; // should be some sort of weak ref.

	};
}