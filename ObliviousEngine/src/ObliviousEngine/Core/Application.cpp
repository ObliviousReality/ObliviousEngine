#include "oepch.h"
#include "Application.h"
#include "Log.h"
//#define SDL_MAIN_HANDLED
#pragma warning(push, 0)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#pragma warning(pop)
//#include "EventHandler.cpp"
//#include "KeyInput.cpp"
#include <GLFW/glfw3.h>
#include <ObliviousEngine/Events/AppEvent.h>


namespace OE {

	Application::Application() {
		window = std::unique_ptr<Window>(Window::createWindow());
	}

	Application::~Application() {

	}

	void Application::run()
	{
		//loop();
		WindowResizeEvent e(10, 10);
		if (e.isInCat(ECApp))
			OE_CORE_TRACE("IS IN APP!");
		while (!crashed)
		{
			window->onUpdate();
		}
	}

	void Application::loop()
	{
		OE_CORE_WARN("This should not be visible - Application::loop() should be overrridden.");
	}

	void Application::init()
	{
		OE_CORE_TRACE("SDL2 Initialising:");
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			OE_CORE_ERROR("SDL Failed to launch. Terminating.");
		}
		OE_CORE_INFO("SDL Launched succesfully.");
		OE_CORE_TRACE("SDL2 Image Initialising:");
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			OE_CORE_ERROR("SDL Image Failed to Launch. Terminating.");
		}
		OE_CORE_INFO("SDL Image launched succesfully.");
		OE_CORE_TRACE("SDL2 Mixer Initialising:");
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			OE_CORE_ERROR("SDL Mixer Failed to Launch. Terminating");
		}
		OE_CORE_INFO("SDL Mixer launched succesfully.");
		OE_CORE_TRACE("SDL2 TTF Initialising:");
		if (TTF_Init() == -1)
		{
			OE_CORE_ERROR("SDL TTF Failed to Launch. Terminating");
		}
		OE_CORE_INFO("SDL TTF launched succesfully.");
		OE_CORE_TRACE("Assigning Mixer Channels:");
		OE_CORE_INFO("{} currently assigned", MIX_CHANNELS);
		Mix_AllocateChannels(16);
		OE_CORE_INFO("{} currently assigned", MIX_CHANNELS);
		OE_CORE_INFO("16 Channels assigned successfully");
		OE_CORE_INFO("Oblivious Engine Online.");
	}

	void Application::quit()
	{
		OE_CORE_TRACE("Quitting SDL:");
		SDL_Quit();
		OE_CORE_ERROR("SDL Quit.");
	}
}