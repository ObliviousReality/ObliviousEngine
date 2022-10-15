#include "oepch.h"
#include "OldEntity.h"

namespace OE {

	OldEntity::OldEntity(int x, int y, Renderer* renderer) : texture(renderer)
	{
		this->x = x;
		this->y = y;
		this->w = texture.getWidth();
		this->h = texture.getHeight();
	}

	OldEntity::~OldEntity()
	{
		texture.free();
	}

	Texture OldEntity::getTexture()
	{
		return texture;
	}

	void OldEntity::setPos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void OldEntity::draw()
	{
		texture.render(x, y);
	}

	void OldEntity::update()
	{
	}

	void OldEntity::onCollide(OldEntity* e)
	{
	}

	int OldEntity::getCollisionClass()
	{
		return 0;
	}

	double OldEntity::getArea()
	{
		return 0;
	}

	double OldEntity::getCircumference()
	{
		return 0;
	}

}