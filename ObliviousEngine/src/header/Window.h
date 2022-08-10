#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <sstream>
class Window
{
public:
	Window();
	~Window();

	SDL_Window* create(const char* name, int w, int h, int size);
	void destroy();
	SDL_Window* getWindow();

private:
	SDL_Window* window;
	bool initFeat();
};

