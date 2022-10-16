#include "oepch.h"
#include "OldWindow.h"
#include <ObliviousEngine/Core/Log.h>

namespace OE {

	OldWindow::OldWindow()
	{
		window = NULL;
	}

	OldWindow::~OldWindow()
	{
		SDL_DestroyWindow(window);
	}

	SDL_Window* OldWindow::create(const char* name, int w, int h, int size)
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
			this->width = width;
			this->height = height;
			this->name = name;
			return window;
		}
		else {
			return NULL;
		}

	}

	void OldWindow::destroy()
	{
		SDL_DestroyWindow(window);
	}

	SDL_Window* OldWindow::getWindow()
	{
		return window;
	}



	bool OldWindow::initFeat()
	{
		if (window == NULL)
		{
			OE_CORE_ERROR("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			OE_CORE_INFO("Window Created Successfully");
		}
		return true;
	}

}