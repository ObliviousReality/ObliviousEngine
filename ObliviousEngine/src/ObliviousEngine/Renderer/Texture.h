#pragma once
#include "Core.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>


namespace OE {
	class OBLIVIOUSENGINE_API Texture
	{
	public:
		Texture();
		~Texture();

		void loadFromFile(std::string path);
		void free();
		//void render(int x, int y);
		int getHeight();
		int getWidth();

		SDL_Texture* getTexture() { return texture; }

	protected:
		//SDL_Renderer* renderer;
		SDL_Texture* texture;

		int width;
		int height;
	};

}