#include "oepch.h"

#include "WinWindow.h"

#include "ObliviousEngine/Core/Input.h"

#include "ObliviousEngine/Events/AppEvent.h"
#include "ObliviousEngine/Events/KeyEvent.h"
#include "ObliviousEngine/Events/MouseEvent.h"

#include "ObliviousEngine/Renderer/Renderer.h"

#include "Platforms/OpenGL/OpenGLContext.h"

namespace OE
{
    static uint8_t GLFWWindowCount = 0;

    static void GLFWErrorCallback(int e, const char * desc) { CORE_ERROR("GLFW Error {0}: {1}", e, desc); }

    WinWindow::WinWindow(const Properties & props)
    {
        PROFILE_FUNCTION();
        init(props);
    }

    WinWindow::~WinWindow()
    {
        PROFILE_FUNCTION();
        close();
    }

    void WinWindow::onUpdate()
    {
        PROFILE_FUNCTION();
        glfwPollEvents();
        context->swapBuffers();
    }

    void WinWindow::setVSync(bool e)
    {
        PROFILE_FUNCTION();
        winProps.vsync = e;
        if (e)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    bool WinWindow::vsynced() const { return winProps.vsync; }

    void WinWindow::init(const Properties & props)
    {
        PROFILE_FUNCTION();
        winProps.height = props.height;
        winProps.width = props.width;
        winProps.name = props.name;

        CORE_INFO("Creating a window.");

        if (GLFWWindowCount == 0)
        {
            CORE_TRACE("Initialising GLFW");
            int success = glfwInit();
            if (!success)
            {
                CORE_ASSERT(success, "COULD NOT INITIALISE GLFW");
                glfwSetErrorCallback(GLFWErrorCallback);
            }
            CORE_TRACE("GLFW Initialised");
        }
        // FULLSCREEN:
        // window = glfwCreateWindow(winProps.width, winProps.height, winProps.name.c_str(), glfwGetPrimaryMonitor(),
        // nullptr);

#ifdef LOG_GL_WARNINGS
        if (Renderer::GetAPI() == RenderAPI::API::OpenGL)
        {
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        }
#endif //  LOG_GL_WARNINGS

        window = glfwCreateWindow(winProps.width, winProps.height, winProps.name.c_str(), nullptr, nullptr);
        ++GLFWWindowCount;

        context = RenderContext::Create(window);
        context->init();

        glfwSetWindowUserPointer(window, &winProps);
        setVSync(true);

        glfwSetWindowSizeCallback(window,
                                  [](GLFWwindow * window, int w, int h)
                                  {
                                      WindowData & data = *(WindowData *)glfwGetWindowUserPointer(window);
                                      data.width = w;
                                      data.height = h;

                                      WindowResizeEvent event(w, h);
                                      // CORE_INFO("WINDOW SIZE: {0} x, {1} y", w, h);
                                      data.callback(event);
                                  });

        glfwSetWindowCloseCallback(window,
                                   [](GLFWwindow * window)
                                   {
                                       WindowData & data = *(WindowData *)glfwGetWindowUserPointer(window);
                                       WindowCloseEvent event;
                                       data.callback(event);
                                   });

        glfwSetKeyCallback(window,
                           [](GLFWwindow * window, int k, int sc, int act, int mod)
                           {
                               WindowData & data = *(WindowData *)glfwGetWindowUserPointer(window);
                               switch (act)
                               {
                                   case GLFW_PRESS:
                                   {
                                       KeyDownEvent ev(static_cast<KeyCode>(k), 0);
                                       data.callback(ev);
                                       break;
                                   }
                                   case GLFW_RELEASE:
                                   {
                                       KeyUpEvent ev(static_cast<KeyCode>(k));
                                       data.callback(ev);
                                       break;
                                   }
                                   case GLFW_REPEAT:
                                   {
                                       KeyDownEvent ev(static_cast<KeyCode>(k), 1);
                                       data.callback(ev);
                                       break;
                                   }
                               }
                           });

        glfwSetCharCallback(window,
                            [](GLFWwindow * window, unsigned int character)
                            {
                                WindowData & data = *(WindowData *)glfwGetWindowUserPointer(window);
                                KeyTypeEvent event(static_cast<KeyCode>(character));
                                data.callback(event);
                            });

        glfwSetMouseButtonCallback(window,
                                   [](GLFWwindow * window, int but, int act, int mod)
                                   {
                                       WindowData & data = *(WindowData *)glfwGetWindowUserPointer(window);
                                       switch (act)
                                       {
                                           case GLFW_PRESS:
                                           {
                                               MouseDownEvent ev(static_cast<MouseCode>(but));
                                               data.callback(ev);
                                               break;
                                           }
                                           case GLFW_RELEASE:
                                           {
                                               MouseUpEvent ev(static_cast<MouseCode>(but));
                                               data.callback(ev);
                                               break;
                                           }
                                       }
                                   });

        glfwSetScrollCallback(window,
                              [](GLFWwindow * window, double xo, double yo)
                              {
                                  WindowData & data = *(WindowData *)glfwGetWindowUserPointer(window);
                                  MouseScrollEvent ev((float)xo, (float)yo);
                                  data.callback(ev);
                              });

        glfwSetCursorPosCallback(window,
                                 [](GLFWwindow * window, double x, double y)
                                 {
                                     WindowData & data = *(WindowData *)glfwGetWindowUserPointer(window);
                                     MouseMoveEvent ev((float)x, (float)y);
                                     data.callback(ev);
                                 });
    }

    void WinWindow::close()
    {
        PROFILE_FUNCTION();
        glfwDestroyWindow(window);

        --GLFWWindowCount;

        if (GLFWWindowCount == 0)
        {
            CORE_INFO("Terminating GLFW, no windows are left.");
            glfwTerminate();
        }
    }

} // namespace OE
