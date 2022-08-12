#include "oepch.h"
#include "Renderer.h"

namespace OE {

	Renderer::Renderer(Window* w, bool softwareFallback, bool hardwareAccel, bool vsync, bool targetTexture)
	{
		renderer = SDL_CreateRenderer(w->getWindow(), -1, (softwareFallback ? SDL_RENDERER_SOFTWARE : 0) | (hardwareAccel ? SDL_RENDERER_ACCELERATED : 0) | (vsync ? SDL_RENDERER_PRESENTVSYNC : 0) | (targetTexture ? SDL_RENDERER_TARGETTEXTURE : 0));
		if (renderer == NULL)
		{
			printf("Renderer could not be created :(\n");
		}
	}

	Renderer::~Renderer()
	{
		SDL_DestroyRenderer(renderer);
	}

	SDL_Renderer* Renderer::getRenderer()
	{
		return renderer;
	}

	void Renderer::setDrawColour(int r, int g, int b, int a)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
	}

	void Renderer::setDrawColour(Colour* c)
	{
		SDL_SetRenderDrawColor(renderer, c->getR(), c->getG(), c->getB(), c->getA());
	}

	void Renderer::clear()
	{
		SDL_RenderClear(renderer);
	}

	void Renderer::render()
	{
		SDL_RenderPresent(renderer);
	}

}