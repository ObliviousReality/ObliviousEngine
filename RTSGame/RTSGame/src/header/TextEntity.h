#pragma once
#include "Text.h"
#include "Object.h"
class TextEntity : public Object
{
public:
	TextEntity(int x, int y, SDL_Renderer* renderer);
	~TextEntity();

	Text getTexture();
	virtual void setPos(int x, int y);
	virtual void draw();
	virtual void update();

protected:
	Text texture;
	int x, y, w, h;
};

