#include "oepch.h"
#include "WinWindow.h"

namespace OE
{
	static bool glfw_init = false;

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
			}
			OE_CORE_INFO("GLFW Initialised");
		}
		window = glfwCreateWindow(winProps.width, winProps.height, winProps.name.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &winProps);
		setVSync(true);
	}

	void WinWindow::close()
	{
		glfwDestroyWindow(window);
	}

}