#include "pch.h"
#include "..\header\Window.h"

Window::Window()
{
	window = NULL;
}

Window::~Window()
{
	SDL_DestroyWindow(window);
}

SDL_Window* Window::create(const char* name, int w, int h, int size)
{
	int flag = 0;
	switch (size)
	{
	case 0:
		flag = SDL_WINDOW_FULLSCREEN;
		break;
	case 1:
		flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
		break;
	case 2:
		flag = SDL_WINDOW_MAXIMIZED;
		break;
	default:
		break;
	}
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
	bool s = initFeat();
	if (s) {
		return window;
	}
	else {
		return NULL;
	}

}

void Window::destroy()
{
	SDL_DestroyWindow(window);
}

SDL_Window* Window::getWindow()
{
	return window;
}



bool Window::initFeat()
{
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("Image library couldn't load :( \n");
			return false;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			printf("SDL_Mixer could not initialise \n");
			return false;
		}
		if (TTF_Init() == -1)
		{
			printf("Could not load SDL_ttf\n");
			return false;
		}

	}
	return true;
}
