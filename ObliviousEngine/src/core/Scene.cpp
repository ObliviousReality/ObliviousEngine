#include "pch.h"
#include "..\header\Scene.h"
#include "../header/FPSCounter.h"
#include "../header/DebugBox.h"

Scene::Scene(SDL_Renderer* renderer)
{
	entities = ObjectList::create();
	FPSCounter* fc = new FPSCounter(100, 100, renderer);
	DebugBox* db = new DebugBox(200, 200, renderer);
	ObjectList::addItem(entities, fc);
	ObjectList::addItem(entities, db);
}

Scene::~Scene()
{
}

void Scene::update()
{
	ObjectList::render(entities);
}
