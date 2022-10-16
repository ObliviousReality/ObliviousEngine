#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H


#include "Core.h"
#include <ObliviousEngine/Events/Event.h>
#include <ObliviousEngine/Events/AppEvent.h>
#include <ObliviousEngine/Core/Window.h>

namespace OE {

	class OBLIVIOUSENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		static void init(); // SDL
		static void quit();
		void run();
		virtual void loop();

		void onEvent(Event& e);
	private:
		std::unique_ptr<Window> window;
		bool crashed = false;
		bool onClose(WindowCloseEvent& e);
	};

	//Client side
	Application* CreateApplication();

}

#endif // !APPLICATION_H