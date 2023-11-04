#include "oepch.h"
#include "Platforms/Win/WinWindow.h"
#include <ObliviousEngine/Events/AppEvent.h>
#include <ObliviousEngine/Events/MouseEvent.h>
#include <ObliviousEngine/Events/KeyEvent.h>
#include "Platforms/OpenGL/OpenGLContext.h"



namespace OE
{
	static uint8_t GLFWWindowCount = 0;

	static void GLFWErrorCallback(int e, const char* desc)
	{
		OE_CORE_ERROR("GLFW Error {0}: {1}", e, desc);
	}

	Scope<Window> Window::WindowCreate(const Properties& props)
	{
		return CreateScope<WinWindow>(props);
	}

	WinWindow::WinWindow(const Properties& props)
	{
		init(props);
	}

	WinWindow::~WinWindow()
	{
		close();
	}

	void WinWindow::onUpdate()
	{
		glfwPollEvents();
		context->swapBuffers();
	}

	void WinWindow::setVSync(bool e)
	{
		winProps.vsync = e;
		if (e)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	bool WinWindow::vsynced() const
	{
		return winProps.vsync;
	}

	void WinWindow::init(const Properties& props)
	{
		winProps.height = props.height;
		winProps.width = props.width;
		winProps.name = props.name;

		OE_CORE_INFO("Creating a window.");

		if (GLFWWindowCount == 0)
		{
			OE_CORE_TRACE("Initialising GLFW");
			int success = glfwInit();
			if (!success)
			{
				OE_CORE_ERROR("GLFW Could not initialise.");
				OE_CORE_ASSERT(success, "ERROR!");
				glfwSetErrorCallback(GLFWErrorCallback);
			}
			OE_CORE_INFO("GLFW Initialised");
		}
		//FULLSCREEN:
		//window = glfwCreateWindow(winProps.width, winProps.height, winProps.name.c_str(), glfwGetPrimaryMonitor(), nullptr);

		window = glfwCreateWindow(winProps.width, winProps.height, winProps.name.c_str(), nullptr, nullptr);
		++GLFWWindowCount;

		context = RenderContext::Create(window);
		context->init();

		glfwSetWindowUserPointer(window, &winProps);
		setVSync(true);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = w;
				data.height = h;

				WindowResizeEvent event(w, h);
				//OE_CORE_INFO("WINDOW SIZE: {0} x, {1} y", w, h);
				data.callback(event);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.callback(event);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int k, int sc, int act, int mod)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (act)
				{
				case GLFW_PRESS:
				{
					KeyDownEvent ev(k, 0);
					data.callback(ev);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyUpEvent ev(k);
					data.callback(ev);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyDownEvent ev(k, 1);
					data.callback(ev);
					break;
				}
				}
			}
		);

		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int character)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypeEvent event(character);
				data.callback(event);
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int but, int act, int mod)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (act)
				{
				case GLFW_PRESS:
				{
					MouseDownEvent ev(but);
					data.callback(ev);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseUpEvent ev(but);
					data.callback(ev);
					break;
				}
				}
			}
		);

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xo, double yo)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrollEvent ev((float)xo, (float)yo);
				data.callback(ev);

			}
		);

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMoveEvent ev((float)x, (float)y);
				data.callback(ev);
			}
		);


	}

	void WinWindow::close()
	{
		glfwDestroyWindow(window);

		--GLFWWindowCount;

		if (GLFWWindowCount == 0)
		{
			OE_CORE_INFO("Terminating GLFW, no windows are left.");
			glfwTerminate();
		}
	}

}