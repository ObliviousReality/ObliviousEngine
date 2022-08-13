#include "oepch.h"
#include "EventHandler.h"
#include <stdio.h>
#include <ObliviousEngine/Core/Log.h>

namespace OE {

	EventHandler::EventHandler() {
	}

	void EventHandler::detectEvents()
	{
		resetKeys();
		mouseMoved = false;
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				OE_CORE_INFO("Key pressed: {}", e.key.keysym.sym);
				pressedKeys[keyPressIndex] = e.key.keysym.sym;
				keyPressIndex++;
				if (keyPressIndex > 99) {
					OE_CORE_WARN("Key buffer exceeded, data will be lost.");
					keyPressIndex = 99;
				}
			}
			else if (e.type == SDL_KEYUP) {
				releasedKeys[keyReleaseIndex] = e.key.keysym.sym;
				keyReleaseIndex++;
				if (keyReleaseIndex > 99) {
					OE_CORE_WARN("Key buffer exceeded, data will be lost.");
					keyReleaseIndex = 99;
				}
			}
			else if (e.type == SDL_MOUSEMOTION) {
				mouseMoved = true;
				SDL_GetMouseState(&mouseX, &mouseY);
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				OE_CORE_INFO("MOUSE EVENT! BUTTON {} has been pressed.", e.button.button);
				mouse[e.button.button] = 1;
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				mouse[e.button.button] = 0;
			}
		}
		//OE_CORE_INFO("Buffer Size: {}", keyPressIndex);
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
		int* temp = new int[2];
		temp[0] = mouseX;
		temp[1] = mouseY;
		return temp;
	}

	void EventHandler::resetKeys()
	{
		keyPressIndex = 0;
		keyReleaseIndex = 0;
	}

	int* EventHandler::getMouseInput()
	{
		return mouse;
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