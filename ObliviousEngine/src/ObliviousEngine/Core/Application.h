#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H


#include "Core.h"
#include <ObliviousEngine/Events/Event.h>
#include <ObliviousEngine/Events/AppEvent.h>
#include <ObliviousEngine/Core/Window.h>
#include <ObliviousEngine/Renderer/LayerStack.h>

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

		void pushLayer(Layer* l);
		void pushOverlay(Layer* l);
	private:
		bool onClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		bool crashed = false;
		LayerStack ls;
	};

	//Client side
	Application* CreateApplication();

}

#endif // !APPLICATION_H