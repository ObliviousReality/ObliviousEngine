#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <sstream>
#include "header/Timer.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "header/Text.h"
#include "header/FPSCounter.h"
#include "header/ObjectList.h"
#include "header/DebugBox.h"
#include "header/MediaPlayer.h"
#include "header/Music.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 2560;
const int SCREEN_HEIGHT = 1440;

void quit() {
	SDL_DestroyWindow(window);
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


void init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("Image library couldn't load :( \n");
				quit();
			}
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				printf("SDL_Mixer could not initialise \n");
				quit();
			}
			if (TTF_Init() == -1)
			{
				printf("Could not load SDL_ttf\n");
				quit();
			}
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created :(\n");
			}
		}
	}
}

void loop() {

	bool crashed = false;
	SDL_Event e;
	ObjectList::ObjectNode* list = ObjectList::create();
	/*TTF_Font* font = TTF_OpenFont("assets/font.ttf", 20);
	if (font == NULL)
	{
		printf("Font failed to load\n");
	}*/
	FPSCounter* fc = new FPSCounter(100, 100, renderer);
	DebugBox* db = new DebugBox(200, 200, renderer);
	ObjectList::addItem(list, fc);
	ObjectList::addItem(list, db);
	Mix_AllocateChannels(16);
	printf("Channels allocated: %i\n", Mix_AllocateChannels(-1));
	Music* music = new Music("assets/ritn.mp3");
	SoundEffect* effect = new SoundEffect("assets/pistol.ogg");
	//Mix_Chunk* effect = Mix_LoadWAV("assets/pistol.ogg");
	MediaPlayer::setGlobalVolume(16);

	if (effect == NULL) {
		printf("Failed to load effect: %s", Mix_GetError());
		quit();
	}
	//SDL_Rect fillRect = { SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20, 100, 100 };
	while (!crashed) {

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				crashed = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym)
				{
				case SDLK_p:
					crashed = true;
					break;
				case SDLK_k:
					MediaPlayer::playMusic(music, 0);
					break;
				case SDLK_h:
					MediaPlayer::playEffect(effect, 0);
					break;
				default:
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0x21, 0x00, 0x7F, 0xFF);
		SDL_RenderClear(renderer);
		ObjectList::render(list);
		SDL_RenderPresent(renderer);
	}
}

int main(int argc, char* args[])
{
	//printf("Hello World!\n");

	init();

	loop();

	quit();

	return 0;
}

