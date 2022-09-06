#include "oepch.h"
#include "TextEntity.h"

namespace OE {

	TextEntity::TextEntity(int x, int y, Renderer* renderer) : texture(renderer)
	{
		this->x = x;
		this->y = y;
		this->w = texture.getWidth();
		this->h = texture.getHeight();
	}

	TextEntity::~TextEntity()
	{
		texture.free();
	}

	Text TextEntity::getTexture()
	{
		return texture;
	}

	void TextEntity::setPos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void TextEntity::draw()
	{
		texture.render(x, y);
	}

	void TextEntity::update()
	{
	}

}