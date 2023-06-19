#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H


#include "Core.h"
#include <ObliviousEngine/Events/Event.h>
#include <ObliviousEngine/Events/AppEvent.h>
#include <ObliviousEngine/Core/Window.h>
#include <ObliviousEngine/Renderer/LayerStack.h>
#include "ObliviousEngine/imgui/ImGuiLayer.h"

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

		inline static Application& Get() { return *instance; }
		inline Window& GetWindow() { return *window; }
	private:
		bool onClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		bool crashed = false;
		LayerStack ls;
	private:
		static Application* instance;
	};

	//Client side
	Application* CreateApplication();

}

#endif // !APPLICATION_H