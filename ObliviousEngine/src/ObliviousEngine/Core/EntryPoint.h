#pragma once
#include <ObliviousEngine/Core/Application.h>
#include <Core.h>
#include <ObliviousEngine/Core/Log.h>

#ifdef OE_PLATFORM_WINDOWS

extern OE::Application* OE::CreateApplication();

int wmain(int argc, char** argv) {

	OE::Log::Init();
	OE::Maths::Init();
	OE_START_PROFILER("Startup", "OEProfile-Startup.json");
	OE_CORE_INFO("Main Started");
	auto app = OE::CreateApplication();
	OE_STOP_PROFILER();
	OE_START_PROFILER("Runtime", "OEProfile-Runtime.json");
	OE_CORE_TRACE("App created");
	app->run();
	OE_STOP_PROFILER();
	OE_CORE_TRACE("App ended.");
	OE_START_PROFILER("Shutdown", "OEProfile-Shutdown.json");
	delete app;
	OE_STOP_PROFILER();
	OE::Application::Quit();
	OE_CORE_INFO("Engine shutting down.");
}

#endif // OE_PLATFORM_WINDOWS
