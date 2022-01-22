#pragma once
#include "Text.h"
class TextEntity
{
public:
	TextEntity(int x, int y, SDL_Renderer* renderer);
	~TextEntity();

	Text getTexture();
	virtual void setPos(int x, int y);
	virtual void draw();
	virtual void update();

	virtual int getX();
	virtual int getY();
	virtual int getWidth();
	virtual int getHeight();

protected:
	Text texture;
	int x, y, w, h;
};

