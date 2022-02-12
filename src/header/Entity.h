#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Object.h"
class Entity : public Object
{
public:
	Entity(int x, int y, SDL_Renderer* renderer);
	~Entity();

	Texture getTexture();
	virtual void setPos(int x, int y);
	virtual void draw();
	virtual void update();


protected:
	Texture texture;
	int x, y, w, h;
};

