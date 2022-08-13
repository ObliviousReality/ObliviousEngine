#include <OE.h>
#include <ObliviousEngine/Core/EntryPoint.h>
#include <filesystem>


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
		Mix_AllocateChannels(16);
		OE_INFO("In loop function of Application");
		OE_ERROR("{}", std::filesystem::current_path());
		OE::Window* window = new OE::Window();
		window->create("Test", 1000, 800, OE::NONE);
		OE::Renderer* renderer = new OE::Renderer(window);
		bool crashed = false;
		OE::EventHandler* handler = new OE::EventHandler();
		OE::InputEvent* quitEvent = new OE::InputEvent(handler);
		quitEvent->addKeyPress(OE::KEY_P);
		OE::InputEvent* playEvent = new OE::InputEvent(handler);
		playEvent->addKeyPress(OE::KEY_HOME);
		playEvent->addKeyPress(OE::KEY_KP_7);
		playEvent->addKeyRelease(OE::KEY_LEFTSHIFT);
		OE::Colour* c = new OE::Colour(255, 23, 23, 0);
		OE::ObjectList::ObjectNode* ol = OE::ObjectList::create();
		OE::FPSCounter* fc = new OE::FPSCounter(100, 100, renderer->getRenderer());
		OE::ObjectList::addItem(ol, fc);
		OE::SoundEffect* se = new OE::SoundEffect("assets/pistol.ogg");
		while (!crashed) {
			handler->detectEvents();
			if (handler->quitPressed() || quitEvent->testEvent()) {
				crashed = true;
			}
			if (playEvent->testEvent())
			{
				OE::MediaPlayer::playEffect(se, 0);
			}
			renderer->setDrawColour(c);
			renderer->clear();
			OE::ObjectList::render(ol);
			renderer->render();
		}
	}
};

OE::Application* OE::CreateApplication() {
	OE_INFO("App created.");
	return new Sandbox();
}

