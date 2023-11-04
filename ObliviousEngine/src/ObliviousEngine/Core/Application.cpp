#include "oepch.h"
#include "ObliviousEngine/Core/Application.h"
#include "Log.h"
#include "ObliviousEngine/Renderer/Renderer.h"

#include "ObliviousEngine/Core/Input.h"
#include <GLFW/glfw3.h>


namespace OE {

	Application* Application::instance = nullptr;



	Application::Application()
	{
		OE_CORE_ASSERT(!instance, "APPLICATION ALREADY EXISTS");
		instance = this;
		window = Window::WindowCreate();
		window->setEventCallback(OE_BIND_EVENT(Application::onEvent));
		window->setVSync(true);

		Renderer::Init();

		imGuiLayer = new ImGuiLayer();
		pushOverlay(imGuiLayer);
	}

	Application::~Application() {
		Renderer::Finish();
	}

	void Application::run()
	{
		//loop();
		while (!crashed)
		{
			float time = (float)glfwGetTime(); // Platform specific
			Timestep ts = time - frameTime;
			frameTime = time;
			if (!minimised) {
				for (Layer* l : ls)
				{
					l->onUpdate(ts);
				}
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
		dispatcher.dispatch<WindowCloseEvent>(OE_BIND_EVENT(Application::onClose));
		dispatcher.dispatch<WindowResizeEvent>(OE_BIND_EVENT(Application::resizeEvent));


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
	bool Application::resizeEvent(WindowResizeEvent& rse)
	{
		if (rse.getWidth() == 0 || rse.getHeight() == 0) {
			minimised = true;
			return false;
		}
		minimised = false;

		Renderer::WindowResize(rse.getWidth(), rse.getHeight());

		return false;
	}
}