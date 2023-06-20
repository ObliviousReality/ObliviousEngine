#include "oepch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace OE
{
	OpenGLContext::OpenGLContext(GLFWwindow* window_in) : window(window_in)
	{
		OE_CORE_ASSERT(window, "WINDOW DOES NOT EXIST");
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OE_CORE_ASSERT(status, "Failed to initialise Glad");
		OE_CORE_INFO("Glad initialised.");

		OE_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		OE_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		OE_CORE_INFO("Version: {0}", glGetString(GL_VERSION));


	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(window);
	}
}