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
#include <glad/glad.h>



namespace OE {

#define BIND_EV(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
		window = std::unique_ptr<Window>(Window::createWindow());
		window->setEventCallback(BIND_EV(Application::onEvent));
	}

	Application::~Application() {

	}

	void Application::run()
	{
		//loop();
		while (!crashed)
		{
			glClearColor(0.8, 0.8, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* l : ls)
			{
				l->onUpdate();
			}
			window->onUpdate();
		}
	}

	void Application::loop()
	{
		OE_CORE_WARN("This should not be visible - Application::loop() should be overrridden.");
	}

	void Application::onEvent(Event& e)
	{
		//OE_CORE_TRACE("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EV(Application::onClose));

		for (auto it = ls.end(); it != ls.begin();)
		{
			(*--it)->onEvent(e);
			if (e.handled)
			{
				break;
			}
		}
	}

	void Application::pushLayer(Layer* l)
	{
		ls.push(l);
	}

	void Application::pushOverlay(Layer* l)
	{
		ls.pushOverlay(l);
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


	bool Application::onClose(WindowCloseEvent& e)
	{
		crashed = true;
		return true;
	}
}