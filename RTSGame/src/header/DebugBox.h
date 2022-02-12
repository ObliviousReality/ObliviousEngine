#pragma once
#include "Entity.h"
class DebugBox : public Entity
{
public:
	DebugBox(int x, int y, SDL_Renderer* renderer);
	~DebugBox();

	void update() override;
};

