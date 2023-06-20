#include "oepch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>

#include "Input.h"

namespace OE {

#define BIND_EV(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	{
		OE_CORE_ASSERT(!instance, "APPLICATION ALREADY EXISTS");
		instance = this;
		window = std::unique_ptr<Window>(Window::createWindow());
		window->setEventCallback(BIND_EV(Application::onEvent));

		imGuiLayer = new ImGuiLayer();
		pushOverlay(imGuiLayer);

		glGenVertexArrays(1, &vertexArr);
		glBindVertexArray(vertexArr);


		float v[3 * 4] = {
			-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f,
			0.0f, -0.5f, 0.0f
		};

		float v2[3 * 4] = {
			-1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f
		};

		vertexBuf.reset(VertexBuffer::Create(v2, sizeof(v2)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indexs[6] = {
			0,1,2,0,2,3
		};
		indexBuf.reset(IndexBuffer::Create(indexs, 6));
		std::string vertexSource = R"(
			#version 330 core

			layout(location=0) in vec3 pos;			
			out vec3 vPos;	

			void main()
			{
				vPos = pos;
				gl_Position = vec4(pos,1.0);
			}
		)";
		std::string fragmentSource = R"(
			#version 330 core

			layout(location=0) out vec4 colour;		
			in vec3 vPos;	

			void main()
			{
				colour = vec4(vPos * 0.5 + 0.5,1.0);
			}
		)";


		shader.reset(new GLShader(vertexSource, fragmentSource));
	}

	Application::~Application() {

	}

	void Application::run()
	{
		//loop();
		while (!crashed)
		{
			//glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
			glClearColor(0, 0, 0, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->bind();

			glBindVertexArray(vertexArr);
			glDrawElements(GL_TRIANGLES, indexBuf->getCount(), GL_UNSIGNED_INT, nullptr);
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

	void Application::init()
	{
		OE_CORE_INFO("Oblivious Engine Online.");
	}

	void Application::quit()
	{
		Application::Get().crashed = true;

	}


	bool Application::onClose(WindowCloseEvent& e)
	{
		crashed = true;
		return true;
	}
}