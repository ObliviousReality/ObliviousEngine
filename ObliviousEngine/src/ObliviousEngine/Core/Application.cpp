#include "oepch.h"
#include "Application.h"
#include "Log.h"
//#define SDL_MAIN_HANDLED
#pragma warning(push, 0)
#include <SDL.h>
#pragma warning(pop)
//#include "EventHandler.cpp"
//#include "KeyInput.cpp"


namespace OE {

	Application::Application() {
	}

	Application::~Application() {

	}

	void Application::run()
	{
		loop();
	}

	void Application::loop()
	{
		OE_CORE_WARN("This should not be visible - Application::loop() should be overrridden.");
	}

	void Application::init()
	{
		OE_CORE_TRACE("SDL2 Initialising:");
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			OE_CORE_ERROR("SDL Failed to launch. Terminating.");
		}
		OE_CORE_INFO("SDL Launched succesfully.");
	}

	void Application::quit()
	{
		OE_CORE_TRACE("Quitting SDL:");
		SDL_Quit();
		OE_CORE_ERROR("SDL Quit.");
	}
}