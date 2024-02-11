#include "oepch.h"

#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace OE
{
    OpenGLContext::OpenGLContext(GLFWwindow * window_in) : window(window_in)
    {
        CORE_ASSERT(window, "WINDOW DOES NOT EXIST");
    }

    void OpenGLContext::init()
    {
        PROFILE_FUNCTION();
        glfwMakeContextCurrent(window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CORE_ASSERT(status, "FAILED TO INITIALISE GLAD");
        CORE_INFO("Glad initialised.");

        CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
        CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
        CORE_INFO("Version: {0}", glGetString(GL_VERSION));

#ifdef ENABLE_ASSERTS
        int versionMajor;
        int versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5),
                       "OBLIVIOUS ENGINRE REQUIRES OPENGL VERSION >4.5!");
#endif
    }

    void OpenGLContext::swapBuffers()
    {
        PROFILE_FUNCTION();
        glfwSwapBuffers(window);
    }
} // namespace OE
