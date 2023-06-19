#include <OE.h>
#include <ObliviousEngine/Core/EntryPoint.h>
#include <filesystem>



class TestLayer : public OE::Layer
{
public:
	TestLayer()
		: Layer("Test!") {}

	void onUpdate() override
	{
		//OE_INFO("TestLayer! update!");
		if (OE::Input::isKeyPressed(KEY_P)) {
			OE_TRACE("P PRESSED");
			OE::Application::quit();
		}
	}

	void onEvent(OE::Event& event) override
	{
		//OE_TRACE("{0}", event);
	}
};


class Sandbox : public OE::Application {
public:
	Sandbox() {
		OE_TRACE("Sandbox Started");
		pushLayer(new TestLayer());
		pushOverlay(new OE::ImGuiLayer());
	}

	~Sandbox() {
		OE_TRACE("Sandbox ended.");
	}

	void loop()
	{
		OE_INFO("In loop function of Application");
	}

};

OE::Application* OE::CreateApplication() {
	OE_INFO("App created.");
	return new Sandbox();
}

