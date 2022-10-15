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
		OE_INFO("In loop function of Application");
		ECSLoop();
		//LLLoop();
	}

	void LLLoop() {

		//OE_INFO("{}", std::filesystem::current_path());
		OE::Window* window = new OE::Window();
		const int width = 2560;
		const int height = 1440;
		window->create("Test", width, height, OE::FULLSCREEN_DESKTOP);
		OE::Renderer* renderer = new OE::Renderer(window, false, false, true, false);
		bool crashed = false;
		OE::EventHandler* handler = new OE::EventHandler();
		OE::InputEvent* quitEvent = new OE::InputEvent(handler);
		quitEvent->addKeyPress(OE::KEY_P);
		OE::InputEvent* playEvent = new OE::InputEvent(handler);
		playEvent->addKeyPress(OE::KEY_HOME);
		playEvent->addKeyPress(OE::KEY_KP_7);
		playEvent->addKeyRelease(OE::KEY_LEFTSHIFT);
		OE::Colour* c = new OE::Colour(200, 200, 23, 0);
		OE::ObjectList::ObjectNode* ol = OE::ObjectList::create();
		OE::FPSCounter* fc = new OE::FPSCounter(100, 100, renderer);
		OE::DebugBox* db = new OE::DebugBox(500, 500, renderer, handler);
		OE::MovingBox* mb = new OE::MovingBox(50, 50, renderer, handler);
		OE::ObjectList::addItem(ol, db);
		OE::ObjectList::addItem(ol, mb);
		OE::ObjectList::addItem(ol, fc);
		OE::SoundEffect* se = new OE::SoundEffect("assets/pistol.ogg");
		while (!crashed) {
			handler->detectEvents();
			if (handler->quitPressed() || quitEvent->testEvent()) {
				OE_TRACE("Quit detected. Closing Window");
				crashed = true;
			}
			if (playEvent->testEvent())
			{
				if (!se->isPlaying()) {
					OE::MediaPlayer::playEffect(se, 0);
				}
			}
			renderer->setDrawColour(c);
			renderer->clear();
			OE::ObjectList::render(ol);
			renderer->render();
		}
	}

	void ECSLoop() {
		//OE_INFO("{}", std::filesystem::current_path());
		OE::Window* window = new OE::Window();
		const int width = 2560;
		const int height = 1440;
		window->create("Test", width, height, OE::FULLSCREEN_DESKTOP);
		OE::Renderer* renderer = new OE::Renderer(window, false, false, true, false);
		bool crashed = false;
		OE::EventHandler* handler = new OE::EventHandler();
		OE::InputEvent* quitEvent = new OE::InputEvent(handler);
		quitEvent->addKeyPress(OE::KEY_P);
		OE::Colour* c = new OE::Colour(200, 200, 23, 0);
		OE::Scene* s = new OE::Scene(renderer, handler);
		for (int i = 0; i < 3; i++) {
			auto box = s->createEntity();
			s->Reg().emplace<OE::TransformComponent>(box, OE::Maths::randomIntRange(0, width - 100), OE::Maths::randomIntRange(0, height - 100));
			s->Reg().emplace<OE::SpriteRendererComponent>(box, OE::Vec3(100, 100, 0));
		}
		auto box = s->createEntity();
		s->Reg().emplace<OE::TransformComponent>(box, OE::Maths::randomIntRange(0, width - 100), OE::Maths::randomIntRange(0, height - 100));
		//s->Reg().emplace<OE::SpriteRendererComponent>(box, OE::Vec3(100, 100, 0));
		while (!crashed) {
			handler->detectEvents();
			if (handler->quitPressed() || quitEvent->testEvent()) {
				OE_TRACE("Quit detected. Closing Window");
				crashed = true;
			}
			renderer->setDrawColour(c);
			renderer->clear();
			s->update();
			renderer->render();
		}
	}
};

OE::Application* OE::CreateApplication() {
	OE_INFO("App created.");
	return new Sandbox();
}

