#include "OE.h"
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

OE::OE()
{
}

void OE::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
}

void OE::exit()
{
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
