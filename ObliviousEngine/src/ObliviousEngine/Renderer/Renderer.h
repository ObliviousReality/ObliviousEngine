#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "Core.h"
#include "Colour.h"
#include <ObliviousEngine/Core/OldWindow.h>
#include <glm/glm.hpp>

namespace OE {

	class OBLIVIOUSENGINE_API Renderer
	{
	public:
		//Renderer(Window* w, bool softwareFallback = false, bool hardwareAccel = false, bool vsync = false, bool targetTexture = false);
		//~Renderer();
		static void SetDrawColour(int r, int g, int b, int a = 0);
		static void SetDrawColour(Colour* c);
		static void BuildRenderer(OldWindow* w, bool softwareFallback = false, bool hardwareAccel = false, bool vsync = false, bool targetTexture = false);
		static void Clear();
		static void Render();
		static void RenderSprite(glm::vec2 pos, glm::vec2 dim, SDL_Texture* t);
		static SDL_Texture* CreateTextureFromSurface(SDL_Surface* s) { return SDL_CreateTextureFromSurface(renderer, s); }
	private:
		static inline SDL_Renderer* renderer = nullptr;
		//SDL_Renderer* getRenderer();
	};

}

#endif // !RENDERER_H