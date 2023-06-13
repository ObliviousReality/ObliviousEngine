#include "oepch.h"
#include "WinWindow.h"
#include <ObliviousEngine/Events/AppEvent.h>
#include <ObliviousEngine/Events/MouseEvent.h>
#include <ObliviousEngine/Events/KeyEvent.h>

#include <glad/glad.h>

namespace OE
{
	static bool glfw_init = false;

	static void GLFWErrorCallback(int e, const char* desc)
	{
		OE_CORE_ERROR("GLFW Error {0}: {1}", e, desc);
	}

	Window* Window::createWindow(const Properties& props)
	{
		return new WinWindow(props);
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
		glfwSwapBuffers(window);
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

		if (!glfw_init)
		{
			OE_CORE_TRACE("Initialising GLFW");
			int success = glfwInit();
			if (!success)
			{
				OE_CORE_ERROR("GLFW Could not initialise.");
				OE_CORE_ASSERT(success, "ERROR!");
				glfwSetErrorCallback(GLFWErrorCallback);
				glfw_init = true;
			}
			OE_CORE_INFO("GLFW Initialised");
		}
		window = glfwCreateWindow(winProps.width, winProps.height, winProps.name.c_str(), glfwGetPrimaryMonitor(), nullptr);
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OE_CORE_ASSERT(status, "Failed to initialise Glad");
		OE_CORE_INFO("Glad initialised.");
		glfwSetWindowUserPointer(window, &winProps);
		setVSync(true);
		//Events motherfucker:

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = w;
				data.height = h;

				WindowResizeEvent event(w, h);
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
	}

}