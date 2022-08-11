#pragma once


#ifdef OE_PLATFORM_WINDOWS

extern OE::Application* OE::CreateApplication();

int wmain(int argc, char** argv) {
	auto app = OE::CreateApplication();
	app->run();
	delete app;
}

#endif // OE_PLATFORM_WINDOWS
