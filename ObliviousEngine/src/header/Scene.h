#include "ObjectList.h"
#include <SDL.h>
#include "EventHandler.h"

class Scene {
public:
	Scene(SDL_Renderer* renderer, EventHandler* handler);
	~Scene();
	void update();

private:
	ObjectList::ObjectNode* entities;
};