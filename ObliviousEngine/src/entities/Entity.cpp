#include "pch.h"
#include "..\header\Entity.h"

Entity::Entity(int x, int y, SDL_Renderer* renderer) : texture(renderer)
{
	this->x = x;
	this->y = y;
	this->w = texture.getWidth();
	this->h = texture.getHeight();
}

Entity::~Entity()
{
	texture.free();
}

Texture Entity::getTexture()
{
	return texture;
}

void Entity::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Entity::draw()
{
	texture.render(x, y);
}

void Entity::update()
{
}
