#include "oepch.h"
#include "WinInput.h"

#include <GLFW/glfw3.h>
#include "ObliviousEngine/Core/Application.h"

namespace OE {

	Input* Input::instance = new WinInput();

	bool WinInput::isKeyPressedImp(int KC)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetKey(window, KC);
		return state == GLFW_PRESS || GLFW_REPEAT;
	}
	bool WinInput::isMousePressedImp(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	float WinInput::getMouseXImp()
	{
		auto [x, y] = getMousePosImp();
		return x;
	}
	float WinInput::getMouseYImp()
	{
		auto [x, y] = getMousePosImp();
		return y;
	}
	std::pair<float, float> WinInput::getMousePosImp()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}
}