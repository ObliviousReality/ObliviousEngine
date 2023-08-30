#include "oepch.h"
#include "Application.h"
#include "Log.h"
#include "ObliviousEngine/Renderer/Renderer.h"

#include "Input.h"
#include <GLFW/glfw3.h>


namespace OE {

#define BIND_EV(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;



	Application::Application()
	{
		OE_CORE_ASSERT(!instance, "APPLICATION ALREADY EXISTS");
		instance = this;
		window = std::unique_ptr<Window>(Window::WindowCreate());
		window->setEventCallback(BIND_EV(Application::onEvent));
		window->setVSync(true);
		imGuiLayer = new ImGuiLayer();
		pushOverlay(imGuiLayer);
	}

	Application::~Application() {

	}

	void Application::run()
	{
		//loop();
		while (!crashed)
		{
			float time = (float)glfwGetTime(); // Platform specific
			Timestep ts = time - frameTime;
			frameTime = time;

			for (Layer* l : ls)
			{
				l->onUpdate(ts);
			}

			imGuiLayer->begin();
			for (Layer* l : ls)
			{
				l->onImGuiRender();
			}
			imGuiLayer->end();

			//auto [x, y] = Input::getMousePos();
			//OE_CORE_TRACE("{0}, {1}", x, y);
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

	void Application::Init()
	{
		OE_CORE_INFO("Oblivious Engine Online.");
	}

	void Application::Quit()
	{
		Application::Get().crashed = true;

	}


	bool Application::onClose(WindowCloseEvent& e)
	{
		crashed = true;
		return true;
	}
}