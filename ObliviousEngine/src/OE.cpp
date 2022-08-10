#include "pch.h"
#include "OE.h"

ObliviousEngine::ObliviousEngine()
{
	printf("HEllo");
}

void ObliviousEngine::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
}

void ObliviousEngine::exit()
{
	SDL_Quit();
}
