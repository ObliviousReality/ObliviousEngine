#include "oepch.h"
#include "Application.h"
#include "Log.h"
#include "ObliviousEngine/Renderer/Renderer.h"

#include "Input.h"


namespace OE {

#define BIND_EV(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;



	Application::Application() : camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		OE_CORE_ASSERT(!instance, "APPLICATION ALREADY EXISTS");
		instance = this;
		window = std::unique_ptr<Window>(Window::WindowCreate());
		window->setEventCallback(BIND_EV(Application::onEvent));

		imGuiLayer = new ImGuiLayer();
		pushOverlay(imGuiLayer);

		vertexArr.reset(VertexArray::Create());

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
		std::shared_ptr<VertexBuffer> vertexBuf;
		vertexBuf.reset(VertexBuffer::Create(rect, sizeof(rect)));

		BufferLayout layout = {
			{ShaderType::Float3, "position"},
			{ShaderType::Float4, "colour"}
		};

		vertexBuf->setLayout(layout);
		vertexArr->addVertexBuffer(vertexBuf);

		unsigned int indexs[6] = {
			0,1,2,0,2,3
		};
		std::shared_ptr<IndexBuffer> indexBuf;
		indexBuf.reset(IndexBuffer::Create(indexs, 6));
		vertexArr->setIndexBuffer(indexBuf);

		float square[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,0.5f,0.0f,
			-0.5f,0.5f,0.0f
		};

		squareArr.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(square, sizeof(square)));

		BufferLayout squareLayout = {
			{ShaderType::Float3, "position"}
		};

		squareVB->setLayout(squareLayout);
		squareArr->addVertexBuffer(squareVB);

		unsigned int squareis[6] = {
			0,1,2,2,3,0
		};
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareis, 6));
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


		shader.reset(new GLShader(vertexSource, fragmentSource));

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


		shader2.reset(new GLShader(vertexSource2, fragmentSource2));
	}

	Application::~Application() {

	}

	void Application::run()
	{
		//loop();
		while (!crashed)
		{
			RenderCommand::SetClearColour(Colour(0, 0, 0, 1.0f));
			RenderCommand::Clear();

			camera.setPos({ 0.5f, 0.5f, 0.0f });
			camera.setRot(45.0f);

			Renderer::BeginScene(camera);
			{
				Renderer::Draw(shader, vertexArr);
				Renderer::Draw(shader2, squareArr);
			}
			Renderer::EndScene();

			for (Layer* l : ls)
			{
				l->onUpdate();
			}

			imGuiLayer->begin();
			for (Layer* l : ls)
			{
				l->onImGuiRender();
			}
			imGuiLayer->end();

			//auto [x, y] = Input::getMousePos();
			//OE_CORE_TRACE("{0}, {1}", x, y);
			window->onUpdate();
		}
	}

	void Application::loop()
	{
		OE_CORE_WARN("This should not be visible - Application::loop() should be overrridden.");
	}

	void Application::onEvent(Event& e)
	{
		//OE_CORE_TRACE("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EV(Application::onClose));

		for (auto it = ls.end(); it != ls.begin();)
		{
			(*--it)->onEvent(e);
			if (e.handled)
			{
				break;
			}
		}
	}

	void Application::pushLayer(Layer* l)
	{
		ls.push(l);
	}

	void Application::pushOverlay(Layer* l)
	{
		ls.pushOverlay(l);
	}

	void Application::Init()
	{
		OE_CORE_INFO("Oblivious Engine Online.");
	}

	void Application::Quit()
	{
		Application::Get().crashed = true;

	}


	bool Application::onClose(WindowCloseEvent& e)
	{
		crashed = true;
		return true;
	}
}