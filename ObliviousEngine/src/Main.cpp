#include "pch.h"
#include "header/Timer.h"
#include "header/MediaPlayer.h"
#include "header/Music.h"
#include "header/Scene.h"
#include "header/Window.h"
#include "header/Renderer.h"
#include "OE.h"

ObliviousEngine* engine = new ObliviousEngine();
Window* window = new Window();
Renderer* renderer = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 2560;
const int SCREEN_HEIGHT = 1440;

void quit() {
	window->destroy();
	engine->exit();
}


void init() {
	engine->init();
	//Create window
	window->create("EPIC WINDOW", SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	if (window->getWindow() == NULL) {
		quit();
	}
	renderer = new Renderer(window, false, true, true, false);
}

void loop() {

	bool crashed = false;
	SDL_Event e;
	/*TTF_Font* font = TTF_OpenFont("assets/font.ttf", 20);
	if (font == NULL)
	{
		printf("Font failed to load\n");
	}*/

	Scene* s = new Scene(renderer->getRenderer());

	Mix_AllocateChannels(16);
	//printf("Channels allocated: %i\n", Mix_AllocateChannels(-1));
	Music* music = new Music("assets/ritn.mp3");
	SoundEffect* effect = new SoundEffect("assets/pistol.ogg");
	if (effect->getEffect() == NULL)
	{
		printf("Error: %s\n", Mix_GetError());
	}
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
					printf("H pressed\n");
					MediaPlayer::playEffect(effect, 0);
					break;
				case SDLK_j:
					MediaPlayer::stop();
					break;
				default:
					break;
				}
			}
		}
		renderer->setDrawColour(0x21, 0x00, 0x7F, 0xFF);
		renderer->clear();
		//ObjectList::render(list);
		s->update();
		renderer->render();
	}
}

int wmain(int argc, char* args[])
{
	//printf("Hello World!\n");

	init();

	loop();

	quit();

	return 0;
}

