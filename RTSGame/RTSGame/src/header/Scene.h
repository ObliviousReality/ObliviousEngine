#include "ObjectList.h"
#include <SDL.h>

class Scene {
public:
	Scene(SDL_Renderer* renderer);
	~Scene();
	void update();
private:
	ObjectList::ObjectNode* entities;
};