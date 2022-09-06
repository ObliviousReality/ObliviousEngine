#pragma once
#include "Core.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <ObliviousEngine/Renderer/Renderer.h>

namespace OE {

	class OBLIVIOUSENGINE_API Texture
	{
	public:
		Texture(Renderer* renderer);
		~Texture();

		bool loadFromFile(std::string path);
		void free();
		void render(int x, int y);
		int getHeight();
		int getWidth();

	protected:
		SDL_Renderer* renderer;
		SDL_Texture* texture;

		int width;
		int height;
	};

}