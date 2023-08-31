#include <OE.h>
#include <ObliviousEngine/Core/EntryPoint.h>
#include <filesystem>

#include "imgui/imgui.h"
#include <glm/glm/ext/matrix_transform.hpp>

class TestLayer : public OE::Layer
{
public:
	TestLayer()
		: Layer("Test!"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPos(0.0f, 0.0f, 0.0f) {
		vertexArr.reset(OE::VertexArray::Create());

		float square[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};


		std::shared_ptr<OE::VertexBuffer> vertexBuf;
		vertexBuf.reset(OE::VertexBuffer::Create(square, sizeof(square)));

		OE::BufferLayout layout = {
			{OE::ShaderType::Float3, "position"}
		};

		vertexBuf->setLayout(layout);
		vertexArr->addVertexBuffer(vertexBuf);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<OE::IndexBuffer> indexBuf;
		indexBuf.reset(OE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		vertexArr->setIndexBuffer(indexBuf);

		std::string vertexSource = R"(
			#version 330 core

			layout(location=0) in vec3 position;

			uniform mat4 u_ViewProj;
			uniform mat4 transform;	
			
			out vec3 vPos;	

			void main()
			{
				vPos = position;
				gl_Position = u_ViewProj * transform * vec4(position, 1.0);	
			}
		)";
		std::string fragmentSource = R"(
			#version 330 core

			layout(location=0) out vec4 colour;		
			in vec3 vPos;

			uniform vec4 u_Colour;

			void main()
			{
				colour = u_Colour;
			}
		)";

		shader.reset(new OE::Shader(vertexSource, fragmentSource));

		//------------------------------------------------------

		triangleArr.reset(OE::VertexArray::Create());

		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<OE::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(OE::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		OE::BufferLayout triangleLayout = {
			{OE::ShaderType::Float3, "position"},
			{OE::ShaderType::Float4, "colour"}
		};
		triangleVertexBuffer->setLayout(triangleLayout);
		triangleArr->addVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0,1,2 };
		std::shared_ptr<OE::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(OE::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		triangleArr->setIndexBuffer(triangleIndexBuffer);


		std::string triangleVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec4 colour;

			uniform mat4 u_ViewProj;
			uniform mat4 transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = position;
				v_Color = colour;
				gl_Position = u_ViewProj * transform * vec4(position, 1.0);	
			}
		)";

		std::string triangleFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		triangleShader.reset(new OE::Shader(triangleVertexSrc, triangleFragmentSrc));
	}

	void onUpdate(OE::Timestep ts) override
	{
		//OE_TRACE("DELTA TIME: {0}s", ts.getSeconds());
		if (OE::Input::isKeyPressed(KEY_P)) {
			OE_TRACE("P PRESSED");
			OE::Application::Quit();
		}
		if (OE::Input::isKeyPressed(KEY_LEFT)) {
			cameraPos.x -= camSpeed * ts;
		}
		if (OE::Input::isKeyPressed(KEY_RIGHT)) {
			cameraPos.x += camSpeed * ts;
		}
		if (OE::Input::isKeyPressed(KEY_UP)) {
			cameraPos.y += camSpeed * ts;
		}
		if (OE::Input::isKeyPressed(KEY_DOWN)) {
			cameraPos.y -= camSpeed * ts;
		}

		if (OE::Input::isKeyPressed(KEY_Q)) {
			cameraRot += rotSpeed * ts;
		}
		if (OE::Input::isKeyPressed(KEY_E)) {
			cameraRot -= rotSpeed * ts;
		}

		if (OE::Input::isKeyPressed(KEY_R)) {
			cameraRot = 0;
			cameraPos.x = 0;
			cameraPos.y = 0;
		}

		OE::RenderCommand::SetClearColour(OE::Colour(0, 0, 0, 1.0f));
		OE::RenderCommand::Clear();

		camera.setPos(cameraPos);
		camera.setRot(cameraRot);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		OE::Colour blue(0.8f, 0.2f, 0.3f);
		OE::Colour red(0.2f, 0.3f, 0.8f);

		OE::Renderer::BeginScene(camera);
		{
			for (int y = 0; y < 20; y++) {
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					if (x % 2 == 0)
					{
						shader->uploadUniformFloat4("u_Colour", red);
					}
					else {
						shader->uploadUniformFloat4("u_Colour", blue);
					}
					OE::Renderer::Draw(shader, vertexArr, transform);
				}
			}
			OE::Renderer::Draw(triangleShader, triangleArr);
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
	std::shared_ptr<OE::Shader> shader;
	std::shared_ptr<OE::VertexArray> vertexArr;

	std::shared_ptr<OE::Shader> triangleShader;
	std::shared_ptr<OE::VertexArray> triangleArr;

	OE::OrthographicCamera camera;

	glm::vec3 cameraPos;
	float camSpeed = 7.0f;

	float cameraRot = 0;
	float rotSpeed = 180.0f;
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

