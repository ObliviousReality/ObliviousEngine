#pragma once
#include <SDL.h>
#include "Texture.h"
class Entity
{
public:
	Entity(int x, int y, SDL_Renderer* renderer);
	~Entity();

	Texture getTexture();
	virtual void setPos(int x, int y);
	virtual void draw();
	virtual void update();

	virtual int getX();
	virtual int getY();
	virtual int getWidth();
	virtual int getHeight();

protected:
	Texture texture;
	int x, y, w, h;
};

