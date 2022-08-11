#include <OE.h>

class Sandbox : public OE::Application {
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

OE::Application* OE::CreateApplication() {
	return new Sandbox();
}

