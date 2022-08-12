#include <OE.h>
#include <ObliviousEngine/Core/EntryPoint.h>
#include <ObliviousEngine/Core/Window.h>
//#include <ObliviousEngine/EventHandler.cpp>
#include <ObliviousEngine/Core/KeyInput.h>

class Sandbox : public OE::Application {
public:
	Sandbox() {
		OE_TRACE("Sandbox Started");
		
		
	}
	~Sandbox() {
		OE_TRACE("Sandbox ended.");
	}

	void loop()
	{
		OE_INFO("In loop function of Application");
		OE::Window* window = new OE::Window();
		window->create("Test", 2560, 1440, OE::MAXIMISED);
		OE::Renderer* renderer = new OE::Renderer(window);
		bool crashed = false;
		OE::EventHandler* handler = new OE::EventHandler();
		OE::KeyInput* quitEvent = new OE::KeyInput(handler);
		quitEvent->addKeyPress(OE::KEY_P);
		OE::Colour* c = new OE::Colour(255, 23, 23, 0);
		while (!crashed) {
			handler->detectEvents();
			if (handler->quitPressed() || quitEvent->testEvent()) {
				crashed = true;
			}
			renderer->setDrawColour(c);
			renderer->clear();
			renderer->render();
		}
	}
};

OE::Application* OE::CreateApplication() {
	OE_INFO("App created.");
	return new Sandbox();
}

