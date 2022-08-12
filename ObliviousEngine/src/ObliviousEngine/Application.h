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
		void init();
		void quit();
		void run();
	private:
		
	};

	//Client side
	Application* CreateApplication();

}

#endif // !APPLICATION_H