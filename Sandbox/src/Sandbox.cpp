#include <OE.h>
#include <ObliviousEngine/EntryPoint.h>
#include <ObliviousEngine/Window.cpp>
//#include <ObliviousEngine/EventHandler.cpp>
#include <ObliviousEngine/KeyInput.cpp>

class Sandbox : public OE::Application {
public:
	Sandbox() {
		OE::Window* window = new OE::Window();
		window->create("Test", 200, 200, 3);
		OE::Renderer* renderer = new OE::Renderer(window);
		OE::Application::init();
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
		quit();
	}
	~Sandbox() {

	}
};

OE::Application* OE::CreateApplication() {
	return new Sandbox();
}

