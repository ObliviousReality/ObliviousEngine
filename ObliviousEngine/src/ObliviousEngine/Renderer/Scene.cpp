#include "oepch.h"
#include "Scene.h"

namespace OE {

	Scene::Scene(SDL_Renderer* renderer, EventHandler* handler)
	{
		entities = ObjectList::create();
		//FPSCounter* fc = new FPSCounter(100, 100, renderer);
		//DebugBox* db = new DebugBox(200, 200, renderer, handler);
		//ObjectList::addItem(entities, fc);
		//ObjectList::addItem(entities, db);

	}

	Scene::~Scene()
	{
	}

	void Scene::update()
	{
		ObjectList::render(entities);
	}

}