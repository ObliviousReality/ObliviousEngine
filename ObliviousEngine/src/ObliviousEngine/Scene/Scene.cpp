#include "oepch.h"
#include "Scene.h"
//

namespace OE {

	Scene::Scene(Renderer* renderer, EventHandler* handler) // 
	{
		this->renderer = renderer;
		this->handler = handler;
	}

	Scene::~Scene()
	{
	}

	void Scene::update()
	{
		auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto g : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(g);
			DebugBox* b = new DebugBox(transform.x, transform.y, renderer, handler);
			b->draw();
		}
	}

	entt::entity Scene::createEntity()
	{
		return registry.create();
	}

}