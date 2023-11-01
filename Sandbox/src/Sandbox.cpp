#include <OE.h>
#include <ObliviousEngine/Core/EntryPoint.h>
#include <filesystem>

#include "imgui/imgui.h"
#include <glm/glm/ext/matrix_transform.hpp>
#include <Platforms/OpenGL/GLShader.h>
#include <glm/glm/gtc/type_ptr.hpp>

class TestLayer : public OE::Layer
{
public:
	TestLayer()
		: Layer("Test!"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPos(0.0f, 0.0f, 0.0f) {
		vertexArr.reset(OE::VertexArray::Create());

		float square[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};


		OE::Ref<OE::VertexBuffer> vertexBuf;
		vertexBuf.reset(OE::VertexBuffer::Create(square, sizeof(square)));

		OE::BufferLayout layout = {
			{OE::ShaderType::Float3, "position"},
			{OE::ShaderType::Float2, "textureCoord"}
		};

		vertexBuf->setLayout(layout);
		vertexArr->addVertexBuffer(vertexBuf);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		OE::Ref<OE::IndexBuffer> indexBuf;
		indexBuf.reset(OE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		vertexArr->setIndexBuffer(indexBuf);

		shader.reset(OE::Shader::Create("assets/shaders/Flat.glsl"));
			

		//------------------------------------------------------

		triangleArr.reset(OE::VertexArray::Create());

		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		OE::Ref<OE::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(OE::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		OE::BufferLayout triangleLayout = {
			{OE::ShaderType::Float3, "position"},
			{OE::ShaderType::Float4, "colour"}
		};
		triangleVertexBuffer->setLayout(triangleLayout);
		triangleArr->addVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0,1,2 };
		OE::Ref<OE::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(OE::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		triangleArr->setIndexBuffer(triangleIndexBuffer);

		triangleShader.reset(OE::Shader::Create("assets/shaders/Triangle.glsl"));

		//------------------------------------------------------


		textureShader.reset(OE::Shader::Create("assets/shaders/Texture.glsl"));

		texture2d = OE::Texture2D::Create("assets/textures/TestImage.png");
		alphaTexture2d = OE::Texture2D::Create("assets/textures/TestAlphaImage.png");


		std::dynamic_pointer_cast<OE::GLShader>(textureShader)->bind();
		std::dynamic_pointer_cast<OE::GLShader>(textureShader)->uploadUniformInt("u_Texture", 0);
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



		OE::RenderCommand::SetClearColour(OE::Colour(0.1f, 0.1f, 0.1f, 1.0f));
		OE::RenderCommand::Clear();

		camera.setPos(cameraPos);
		camera.setRot(cameraRot);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));

		std::dynamic_pointer_cast<OE::GLShader>(shader)->bind();
		std::dynamic_pointer_cast<OE::GLShader>(shader)->uploadUniformFloat3("u_Colour", squareColour);


		OE::Renderer::BeginScene(camera);
		{
			for (int y = 0; y < 20; y++) {
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * (scaleFactor + (scaleFactor * 0.1f)), y * (scaleFactor + (scaleFactor * 0.1f)), 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					OE::Renderer::Draw(shader, vertexArr, transform);
				}
			}
			texture2d->bind();
			OE::Renderer::Draw(textureShader, vertexArr, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			alphaTexture2d->bind();
			OE::Renderer::Draw(textureShader, vertexArr, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
			//OE::Renderer::Draw(triangleShader, triangleArr);
		}
		OE::Renderer::EndScene();
	}

	virtual void onImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Colour", glm::value_ptr(squareColour));
		ImGui::End();
	}

	void onEvent(OE::Event& event) override
	{
		OE::EventDispatcher dispatcher(event);
		dispatcher.dispatch<OE::KeyDownEvent>(OE_BIND_EVENT(TestLayer::onKeyPressedEvent));

	}

	bool onKeyPressedEvent(OE::KeyDownEvent& e) {
		switch (e.getKeyCode())
		{
		case KEY_EQUAL:
			scaleFactor += 0.1f;
			break;

		case KEY_MINUS:
			scaleFactor -= 0.1f;
			break;

		default:
			break;
		}
		return false;
	}
private:
	OE::Ref<OE::Shader> shader, textureShader;
	OE::Ref<OE::VertexArray> vertexArr;

	OE::Ref<OE::Shader> triangleShader;
	OE::Ref<OE::VertexArray> triangleArr;

	OE::Ref<OE::Texture2D> texture2d, alphaTexture2d;

	OE::OrthographicCamera camera;

	glm::vec3 cameraPos;
	float camSpeed = 7.0f;

	float cameraRot = 0;
	float rotSpeed = 180.0f;
	float scaleFactor = 0.1f;

	glm::vec3 squareColour = { 0.2f, 0.3f, 0.8f };
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

