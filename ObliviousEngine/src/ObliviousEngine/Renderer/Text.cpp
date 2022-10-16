#include "oepch.h"
#include "Text.h"
//#include "Renderer.h"

namespace OE {

	Text::Text()
	{
	}

	Text::~Text()
	{
		free();
	}

	bool Text::loadText(std::string text, SDL_Colour textColour, TTF_Font* font)
	{
		/*free();
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);
		if (textSurface == NULL)
		{
			printf("Unable to render surface.\n");
		}
		else
		{
			texture = Renderer::CreateTextureFromSurface(textSurface);
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
		return texture != NULL;*/
		return false;
	}

	void Text::free()
	{
		if (texture != NULL)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
			width = 0;
			height = 0;
		}
	}

}