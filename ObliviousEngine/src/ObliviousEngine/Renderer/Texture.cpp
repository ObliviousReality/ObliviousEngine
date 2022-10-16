#include "oepch.h"
#include "Texture.h"
#include <ObliviousEngine/Renderer/Renderer.h>

namespace OE {

	Texture::Texture()
	{
		//this->renderer = renderer->getRenderer();
		texture = NULL;
		width = 0;
		height = 0;
	}

	Texture::~Texture()
	{
		printf("Texture is ded\n");
		free();
	}

	void Texture::loadFromFile(std::string path)
	{
		free();
		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			OE_CORE_WARN("Error loading image");
		}
		else
		{
			newTexture = Renderer::CreateTextureFromSurface(loadedSurface);
			if (newTexture == NULL)
			{
				OE_CORE_WARN("Failed to load texture");
			}
			else
			{
				width = loadedSurface->w;
				height = loadedSurface->h;
			}
			SDL_FreeSurface(loadedSurface);
		}
		OE_CORE_TRACE("Before assignment");
		texture = newTexture;
		OE_CORE_TRACE("After Assignment");
	}

	void Texture::free()
	{
		if (texture != NULL)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
			width = 0;
			height = 0;
		}
	}

	/*void Texture::render(int x, int y)
	{
		SDL_Rect renderQuad = { x, y, width, height };
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
	}*/

	int Texture::getHeight()
	{
		return height;
	}

	int Texture::getWidth()
	{
		return width;
	}

}