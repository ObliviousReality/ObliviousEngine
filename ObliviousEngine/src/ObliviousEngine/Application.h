#pragma once

#include "Core.h"

namespace OE {

	class OBLIVIOUSENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	//Client side
	Application* CreateApplication();

}

