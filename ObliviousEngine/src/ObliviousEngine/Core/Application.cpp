#include "oepch.h"
#include "Application.h"
#include "Log.h"
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
		OE_CORE_INFO("Oblivious Engine Online.");
	}

	void Application::quit()
	{
	}


	bool Application::onClose(WindowCloseEvent& e)
	{
		crashed = true;
		return true;
	}
}