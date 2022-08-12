#pragma once
#include "Core.h"
#include "TextEntity.h"
#include "ObliviousEngine/Core/Timer.h"
#include <SDL_ttf.h>

namespace OE {

	class FPSCounter : public TextEntity
	{
	public:
		FPSCounter(int x, int y, SDL_Renderer* renderer);
		~FPSCounter();
		void draw() override;
		void update() override;
	private:
		Timer timer;
		TTF_Font* font;
		SDL_Colour fontColour;
		int countedFrames = 0;
		int avgFPS = 0;
		std::stringstream timeText;
	};

}