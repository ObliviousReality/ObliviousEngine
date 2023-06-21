#include "oepch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>

#include "Input.h"

namespace OE {

#define BIND_EV(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	static GLenum ShaderTypeToGLType(ShaderType st)
	{
		switch (st)
		{
		case OE::ShaderType::None:
			return 0;
		case OE::ShaderType::Float:
			return GL_FLOAT;
		case OE::ShaderType::Float2:
			return GL_FLOAT;
		case OE::ShaderType::Float3:
			return GL_FLOAT;
		case OE::ShaderType::Float4:
			return GL_FLOAT;
		case OE::ShaderType::Mat3:
			return GL_FLOAT;
		case OE::ShaderType::Mat4:
			return GL_FLOAT;
		case OE::ShaderType::Int:
			return GL_INT;
		case OE::ShaderType::Int2:
			return GL_INT;
		case OE::ShaderType::Int3:
			return GL_INT;
		case OE::ShaderType::Int4:
			return GL_INT;
		case OE::ShaderType::Bool:
			return GL_BOOL;
		default:
			OE_CORE_ASSERT(false, "UNKNOWN SHADER TYPE");
			return 0;
		}
	}

	Application::Application()
	{
		OE_CORE_ASSERT(!instance, "APPLICATION ALREADY EXISTS");
		instance = this;
		window = std::unique_ptr<Window>(Window::WindowCreate());
		window->setEventCallback(BIND_EV(Application::onEvent));

		imGuiLayer = new ImGuiLayer();
		pushOverlay(imGuiLayer);

		glGenVertexArrays(1, &vertexArr);
		glBindVertexArray(vertexArr);


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

		vertexBuf.reset(VertexBuffer::Create(rect, sizeof(rect)));

		{
			BufferLayout layout = {
				{ShaderType::Float3, "position"},
				{ShaderType::Float4, "colour"}
			};
			vertexBuf->setLayout(layout);
		}
		uint32_t ind = 0;
		const auto& layout = vertexBuf->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(ind);
			glVertexAttribPointer(ind, element.getComponentCount(), ShaderTypeToGLType(element.type), element.normalised ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)element.offset);
			ind++;
		}

		unsigned int indexs[6] = {
			0,1,2,0,2,3
		};
		indexBuf.reset(IndexBuffer::Create(indexs, 6));
		std::string vertexSource = R"(
			#version 330 core

			layout(location=0) in vec3 pos;
			layout(location=1) in vec4 colour;			
			
			out vec3 vPos;	

			out vec4 vColour;

			void main()
			{
				vPos = pos;
				vColour = colour;
				gl_Position = vec4(pos,1.0);
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