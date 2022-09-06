#include "oepch.h"
#include "Texture.h"


namespace OE {

	Texture::Texture(Renderer* renderer)
	{
		this->renderer = renderer->getRenderer();
		texture = NULL;
		width = 0;
		height = 0;
	}

	Texture::~Texture()
	{
		printf("Texture is ded\n");
		free();
	}

	bool Texture::loadFromFile(std::string path)
	{
		free();
		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Error loading image\n");
		}
		else
		{
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Failed to load texture\n");
			}
			else
			{
				width = loadedSurface->w;
				height = loadedSurface->h;
			}
			SDL_FreeSurface(loadedSurface);
		}
		texture = newTexture;
		return texture != NULL;
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

	void Texture::render(int x, int y)
	{
		SDL_Rect renderQuad = { x, y, width, height };
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
	}

	int Texture::getHeight()
	{
		return height;
	}

	int Texture::getWidth()
	{
		return width;
	}

}