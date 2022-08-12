#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H


#include "Core.h"

namespace OE {

	class OBLIVIOUSENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		static void init();
		static void quit();
		void run();
		virtual void loop();
	private:
		
	};

	//Client side
	Application* CreateApplication();

}

#endif // !APPLICATION_H