#include "oepch.h"
#include "Entity.h"

namespace OE {

	Entity::Entity(int x, int y, Renderer* renderer) : texture(renderer)
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

	double Entity::getArea()
	{
		return 0;
	}

	double Entity::getCircumference()
	{
		return 0;
	}

}