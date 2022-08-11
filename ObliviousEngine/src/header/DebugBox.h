#pragma once
#include "Entity.h"
#include "../header/KeyInput.h"
class DebugBox : public Entity
{
public:
	DebugBox(int x, int y, SDL_Renderer* renderer, EventHandler* handler);
	~DebugBox();

	void update() override;
private:
	KeyInput* k;
};

