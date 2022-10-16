#include <OE.h>
#include <ObliviousEngine/Core/EntryPoint.h>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
	}

	void ECSLoop() {
		//OE_INFO("{}", std::filesystem::current_path());
		OE::Window* window = new OE::Window();
		const int width = 2560;
		const int height = 1440;
		window->create("Test", width, height, OE::FULLSCREEN_DESKTOP);
		//OE::Renderer* renderer = new OE::Renderer(window, false, false, true, false);
		OE::Renderer::BuildRenderer(window, false, false, true, false);
		bool crashed = false;
		OE::EventHandler* handler = new OE::EventHandler();
		OE::InputEvent* quitEvent = new OE::InputEvent(handler);
		quitEvent->addKeyPress(OE::KEY_P);
		OE::Colour* c = new OE::Colour(200, 200, 23, 0);
		OE::Scene* s = new OE::Scene();
		for (int i = 0; i < 3; i++) {
			OE::Entity e = s->createEntity(std::to_string(i));
			OE_CORE_TRACE("Entity created.");
			e.getComp<OE::TransformComponent>().vec = glm::vec2(OE::Maths::randomIntRange(0, width - 100), OE::Maths::randomIntRange(0, height - 100));
			OE_CORE_TRACE("Transform altered.");
			e.addComp<OE::SpriteRendererComponent>(10);
			OE_CORE_TRACE("Asset added.");
		}
		OE::Entity entity = s->createEntity("gary");
		entity.getComp<OE::TransformComponent>().vec = glm::vec2(OE::Maths::randomIntRange(0, width - 100), OE::Maths::randomIntRange(0, height - 100));
		entity.addComp<OE::SpriteRendererComponent>(20);
		if (entity.hasComp<OE::SpriteRendererComponent>())
		{
			OE_CORE_WARN("HAS COMPONENT!");
		}
		/*OE::Entity camera = s->createEntity("Camera");
		camera.addComp<OE::CameraComponent>(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		camera.getComp<OE::CameraComponent>().primary = true;*/
		while (!crashed) {
			handler->detectEvents();
			if (handler->quitPressed() || quitEvent->testEvent()) {
				OE_TRACE("Quit detected. Closing Window");
				crashed = true;
			}
			OE::Renderer::SetDrawColour(c);
			OE::Renderer::Clear();
			s->update();
			OE::Renderer::Render();
		}
	}
};

OE::Application* OE::CreateApplication() {
	OE_INFO("App created.");
	return new Sandbox();
}

