#include "oepch.h"
#include "Window.h"
#include <ObliviousEngine/Core/Log.h>

namespace OE {

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
		OE_CORE_TRACE("Initialising Window");
		int flag = 0;
		switch (size)
		{
		case NONE:
			OE_CORE_TRACE("No Size Specification");
			break;
		case FULLSCREEN:
			OE_CORE_TRACE("Fullscreen Window");
			flag = SDL_WINDOW_FULLSCREEN;
			break;
		case FULLSCREEN_DESKTOP:
			OE_CORE_TRACE("Fullscreen Desktop Window");
			flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
			break;
		case MAXIMISED:
			OE_CORE_TRACE("Maximised Window");
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
			OE_CORE_ERROR("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			OE_CORE_INFO("Window Created Successfully");
			/*int imgFlags = IMG_INIT_PNG;
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
			}*/

		}
		return true;
	}

}