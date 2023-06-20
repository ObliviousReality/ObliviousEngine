#pragma once
#include "ObliviousEngine/Renderer/RenderContext.h"

struct GLFWwindow;

namespace OE
{
	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* window_in);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* window;
	};
}