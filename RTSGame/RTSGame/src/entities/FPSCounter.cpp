#include "../header/FPSCounter.h"

FPSCounter::FPSCounter(int x, int y, SDL_Renderer* renderer) : TextEntity(x, y, renderer)
{
	this->x = x;
	this->y = y;
	this->font = TTF_OpenFont("assets/font.ttf", 20);
	timeText.str("");
	fontColour = { 0,0,0,255 };
	timer.start();
}

FPSCounter::~FPSCounter()
{
}

void FPSCounter::draw()
{
	timeText.str("");
	timeText << avgFPS;
	texture.loadText(timeText.str(), fontColour, font);
	texture.render(x, y);
}

void FPSCounter::update()
{
	++countedFrames;
	avgFPS = countedFrames / (timer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
}
