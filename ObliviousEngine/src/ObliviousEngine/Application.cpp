#include "Application.h"
#include "Log.h"
//#define SDL_MAIN_HANDLED
#include <SDL.h>
//#include "EventHandler.cpp"
//#include "KeyInput.cpp"


namespace OE {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::run()
	{
		OE_TRACE("Application Started");
	}
	void Application::init()
	{
		OE_CORE_TRACE("SDL2 Initialising:");
		SDL_SetMainReady();
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			OE_CORE_ERROR("SDL Failed to launch. Terminating.");
		}
		OE_CORE_INFO("SDL Launched succesfully.");
	}
	void Application::quit()
	{
		OE_CORE_TRACE("Quitting SDL.");
		SDL_Quit();
		OE_CORE_ERROR("SDL Quit.");
	}
}