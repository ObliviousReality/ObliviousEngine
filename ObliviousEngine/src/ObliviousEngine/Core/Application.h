#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H


#include "Core.h"
#include <ObliviousEngine/Events/Event.h>
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
	private:
		std::unique_ptr<Window> window;
		bool crashed = false;
	};

	//Client side
	Application* CreateApplication();

}

#endif // !APPLICATION_H