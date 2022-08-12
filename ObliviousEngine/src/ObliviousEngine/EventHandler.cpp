#include "EventHandler.h"
#include <stdio.h>

namespace OE {

	EventHandler::EventHandler() {
	}

	void EventHandler::detectEvents()
	{
		mouseMoved = false;
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				printf("Key pressed: %i\n", e.key.keysym.sym);
				pressedKeys[keyPressIndex] = e.key.keysym.sym;
				keyPressIndex++;
				if (keyPressIndex > 99) {
					keyPressIndex = 99;
				}
			}
			else if (e.type == SDL_KEYUP) {
				releasedKeys[keyReleaseIndex] = e.key.keysym.sym;
				keyReleaseIndex++;
				if (keyReleaseIndex > 99) {
					keyReleaseIndex = 99;
				}
			}
			else if (e.type == SDL_MOUSEMOTION) {
				mouseMoved = true;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				printf("MOUSE EVENT! BUTTON + %i has been pressed.\n", e.button.button);
				mouse[e.button.button] = 1;
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				printf("MOUSE EVENT! BUTTON + %i has been pressed.\n", e.button.button);
				mouse[e.button.button] = 0;
			}
		}
	}

	bool EventHandler::quitPressed()
	{
		return quit;
	}

	bool EventHandler::mouseMovedSinceLastFrame()
	{
		return mouseMoved;
	}

	int* EventHandler::getMouseXY()
	{
		return nullptr;
	}

	void EventHandler::resetKeys()
	{
		keyPressIndex = 0;
		keyReleaseIndex = 0;
	}

	int* EventHandler::mouseInput()
	{
		return nullptr;
	}

	int* EventHandler::getPressedKeys()
	{
		return pressedKeys;
	}

	int EventHandler::getNumPressedKeys()
	{
		return keyPressIndex;
	}

	int* EventHandler::getReleasedKeys()
	{
		return releasedKeys;
	}

	int EventHandler::getNumReleasedKeys()
	{
		return keyReleaseIndex;
	}

}