#include <OE.h>
#include <ObliviousEngine/Core/EntryPoint.h>
#include <filesystem>

#include "imgui/imgui.h"

class TestLayer : public OE::Layer
{
public:
	TestLayer()
		: Layer("Test!"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPos(0.0f, 0.0f, 0.0f) {
		vertexArr.reset(OE::VertexArray::Create());

		float triangle[3 * 3] = {
			-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		float rect[4 * 7] = {
			-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		std::shared_ptr<OE::VertexBuffer> vertexBuf;
		vertexBuf.reset(OE::VertexBuffer::Create(rect, sizeof(rect)));

		OE::BufferLayout layout = {
			{OE::ShaderType::Float3, "position"},
			{OE::ShaderType::Float4, "colour"}
		};

		vertexBuf->setLayout(layout);
		vertexArr->addVertexBuffer(vertexBuf);

		unsigned int indexs[6] = {
			0,1,2,0,2,3
		};
		std::shared_ptr<OE::IndexBuffer> indexBuf;
		indexBuf.reset(OE::IndexBuffer::Create(indexs, 6));
		vertexArr->setIndexBuffer(indexBuf);

		float square[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,0.5f,0.0f,
			-0.5f,0.5f,0.0f
		};

		squareArr.reset(OE::VertexArray::Create());
		std::shared_ptr<OE::VertexBuffer> squareVB;
		squareVB.reset(OE::VertexBuffer::Create(square, sizeof(square)));

		OE::BufferLayout squareLayout = {
			{OE::ShaderType::Float3, "position"}
		};

		squareVB->setLayout(squareLayout);
		squareArr->addVertexBuffer(squareVB);

		unsigned int squareis[6] = {
			0,1,2,2,3,0
		};
		std::shared_ptr<OE::IndexBuffer> squareIB;
		squareIB.reset(OE::IndexBuffer::Create(squareis, 6));
		squareArr->setIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 330 core

			layout(location=0) in vec3 pos;
			layout(location=1) in vec4 colour;	

			uniform mat4 u_ViewProj;		
			
			out vec3 vPos;	

			out vec4 vColour;

			void main()
			{
				vPos = pos;
				vColour = colour;
				gl_Position = u_ViewProj * vec4(pos,1.0);
			}
		)";
		std::string fragmentSource = R"(
			#version 330 core

			layout(location=0) out vec4 colour;		
			in vec3 vPos;	
			in vec4 vColour;

			void main()
			{
				colour = vec4(vPos * 0.5 + 0.5,1.0);
				colour = vColour;
			}
		)";


		shader.reset(new OE::GLShader(vertexSource, fragmentSource));

		std::string vertexSource2 = R"(
			#version 330 core

			layout(location=0) in vec3 pos;
			
			uniform mat4 u_ViewProj;	

			out vec3 vPos;	
			void main()
			{
				vPos = pos;
				gl_Position = u_ViewProj * vec4(pos,1.0);
			}
		)";
		std::string fragmentSource2 = R"(
			#version 330 core

			layout(location=0) out vec4 colour;		
			in vec3 vPos;	

			void main()
			{
				colour = vec4(0.8,0.8,0.2,1.0);
			}
		)";


		shader2.reset(new OE::GLShader(vertexSource2, fragmentSource2));
	}

	void onUpdate() override
	{
		if (OE::Input::isKeyPressed(KEY_P)) {
			OE_TRACE("P PRESSED");
			OE::Application::Quit();
		}
		if (OE::Input::isKeyPressed(KEY_LEFT)) {
			cameraPos.x -= camSpeed;
		}
		if (OE::Input::isKeyPressed(KEY_RIGHT)) {
			cameraPos.x += camSpeed;
		}
		if (OE::Input::isKeyPressed(KEY_UP)) {
			cameraPos.y += camSpeed;
		}
		if (OE::Input::isKeyPressed(KEY_DOWN)) {
			cameraPos.y -= camSpeed;
		}

		if (OE::Input::isKeyPressed(KEY_Q)) {
			cameraRot += rotSpeed;
		}
		if (OE::Input::isKeyPressed(KEY_E)) {
			cameraRot -= rotSpeed;
		}

		OE::RenderCommand::SetClearColour(OE::Colour(0, 0, 0, 1.0f));
		OE::RenderCommand::Clear();

		camera.setPos(cameraPos);
		camera.setRot(cameraRot);

		OE::Renderer::BeginScene(camera);
		{
			OE::Renderer::Draw(shader, vertexArr);
			OE::Renderer::Draw(shader2, squareArr);
		}
		OE::Renderer::EndScene();
	}

	virtual void onImGuiRender() override
	{
	}

	void onEvent(OE::Event& event) override
	{
		OE::EventDispatcher dispatcher(event);
		dispatcher.dispatch<OE::KeyDownEvent>(OE_BIND_EVENT(TestLayer::onKeyPressedEvent));

	}

	bool onKeyPressedEvent(OE::KeyDownEvent& e) {
		/*switch (e.getKeyCode())
		{
		case KEY_LEFT:
			cameraPos.x -= camSpeed;
			break;
		case KEY_RIGHT:
			cameraPos.x += camSpeed;
			break;
		case KEY_DOWN:
			cameraPos.y -= camSpeed;
			break;
		case KEY_UP:
			cameraPos.y += camSpeed;
			break;
		case KEY_P:
			OE_TRACE("P PRESSED");
			OE::Application::Quit();
			break;
		default:
			break;
		}*/
		return false;
	}
private:
	std::shared_ptr<OE::GLShader> shader;
	std::shared_ptr<OE::VertexArray> vertexArr;

	std::shared_ptr<OE::GLShader> shader2;
	std::shared_ptr<OE::VertexArray> squareArr;

	OE::OrthographicCamera camera;

	glm::vec3 cameraPos;
	float camSpeed = 0.1f;

	float cameraRot = 0;
	float rotSpeed = 0.1f;
};


class Sandbox : public OE::Application {
public:
	Sandbox() {
		OE_TRACE("Sandbox Started");
		pushLayer(new TestLayer());
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

