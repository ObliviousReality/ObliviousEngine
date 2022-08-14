#pragma once
#include <ObliviousEngine/Core/Application.h>
#include <Core.h>
#include <ObliviousEngine/Core/Log.h>

#ifdef OE_PLATFORM_WINDOWS

extern OE::Application* OE::CreateApplication();

int wmain(int argc, char** argv) {

	OE::Log::init();
	OE::Maths::init();
	OE::Application::init();
	OE_CORE_INFO("Main Started");
	auto app = OE::CreateApplication();
	OE_CORE_TRACE("App created");
	OE_CORE_TRACE("Running app.");
	app->run();
	OE_CORE_TRACE("App ended.");
	delete app;
	OE::Application::quit();
	OE_CORE_INFO("Engine shutting down.");
}

#endif // OE_PLATFORM_WINDOWS
