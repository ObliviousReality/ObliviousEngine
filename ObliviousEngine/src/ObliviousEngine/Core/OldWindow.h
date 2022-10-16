#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include "Core.h"
#pragma warning(push, 0)
#include <SDL.h>
#pragma warning(pop)
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <sstream>

namespace OE {

	const typedef enum {
		NONE,
		FULLSCREEN,
		FULLSCREEN_DESKTOP,
		MAXIMISED,
	} OEResolution;

	class OBLIVIOUSENGINE_API OldWindow
	{
	public:
		OldWindow();
		~OldWindow();

		SDL_Window* create(const char* name, int w, int h, int size = 0);
		void destroy();
		SDL_Window* getWindow();

		int width, height;
		const char* name;

	private:
		SDL_Window* window;
		bool initFeat();
	};

}

#endif