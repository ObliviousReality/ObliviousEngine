#pragma once
#include "Window.h"
#include "Colour.h"
class Renderer
{
public:
	Renderer(Window* w, bool softwareFallback = false, bool hardwareAccel = false, bool vsync = false, bool targetTexture = false);
	~Renderer();
	SDL_Renderer* getRenderer();
	void setDrawColour(int r, int g, int b, int a = 0);
	void setDrawColour(Colour c);
	void clear();
	void render();
private:
	SDL_Renderer* renderer;
};

