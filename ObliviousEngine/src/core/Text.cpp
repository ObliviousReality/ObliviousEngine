#include "pch.h"
#include "../header/Text.h"


Text::Text(SDL_Renderer* renderer) : Texture(renderer)
{
	this->renderer = renderer;
}

Text::~Text()
{
	free();
}

bool Text::loadText(std::string text, SDL_Colour textColour, TTF_Font* font)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);
	if (textSurface == NULL)
	{
		printf("Unable to render surface\n");
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			printf("Unable to create text texture\n");
		}
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return texture != NULL;
}
