#include "oepch.h"
#include "Scene.h"
#include "Entity.h"

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

	Entity Scene::createEntity(const std::string& name)
	{
		Entity temp = { registry.create(), this };
		temp.addComp<TransformComponent>();
		auto& tag = temp.addComp<TagComponent>();
		tag.tag = name.empty() ? "Unnamed Entity" : name;
		return temp;
	}

}