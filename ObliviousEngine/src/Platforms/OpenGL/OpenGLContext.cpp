#include "oepch.h"

#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace OE
{
    OpenGLContext::OpenGLContext(GLFWwindow * window_in) : window(window_in)
    {
        OE_CORE_ASSERT(window, "WINDOW DOES NOT EXIST");
    }

    void OpenGLContext::init()
    {
        OE_PROFILE_FUNCTION();
        glfwMakeContextCurrent(window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        OE_CORE_ASSERT(status, "FAILED TO INITIALISE GLAD");
        OE_CORE_INFO("Glad initialised.");

        OE_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
        OE_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
        OE_CORE_INFO("Version: {0}", glGetString(GL_VERSION));

#ifdef OE_ENABLE_ASSERTS
        int versionMajor;
        int versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        OE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5),
                       "OBLIVIOUS ENGINRE REQUIRES OPENGL VERSION >4.5!");
#endif
    }

    void OpenGLContext::swapBuffers()
    {
        OE_PROFILE_FUNCTION();
        glfwSwapBuffers(window);
    }
} // namespace OE
