#include "oepch.h"

#include "WinInput.h"

#include "ObliviousEngine/Core/Application.h"

#include <GLFW/glfw3.h>

namespace OE
{
    bool WinInput::isKeyPressedImp(KeyCode KC)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(KC));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WinInput::isMousePressedImp(MouseCode button)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
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
        auto window = static_cast<GLFWwindow *>(Application::Get().getWindow().getNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return { (float)x, (float)y };
    }
} // namespace OE
