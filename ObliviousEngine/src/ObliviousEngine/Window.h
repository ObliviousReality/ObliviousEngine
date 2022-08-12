#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include "Core.h"
//#define SDL_MAIN_HANDLED
#include <SDL.h>
//#include <SDL_ttf.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
#include <stdio.h>
#include <sstream>

namespace OE {

	class OBLIVIOUSENGINE_API Window
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

}

#endif