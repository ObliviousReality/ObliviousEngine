#include "oepch.h"

#include "Application.h"
#include "Input.h"
#include "Log.h"

#include "ObliviousEngine/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace OE
{
    Application * Application::instance = nullptr;

    Application::Application()
    {
        PROFILE_FUNCTION();
        CORE_ASSERT(!instance, "APPLICATION ALREADY EXISTS");
        instance = this;
        window = Window::WindowCreate(Properties("Sandbox!", 1920, 1080));
        window->setEventCallback(BIND_EVENT(Application::onEvent));
        window->setVSync(true);

        Renderer::Init();

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);
    }

    Application::~Application()
    {
        PROFILE_FUNCTION();
        Renderer::Finish();
    }

    void Application::run()
    {
        PROFILE_FUNCTION();
        while (!crashed)
        {
            PROFILE_SCOPE("Individual Run Loop");

            float time = (float)glfwGetTime(); // Platform specific
            Timestep ts = time - frameTime;
            frameTime = time;
            if (!minimised)
            {
                {
                    PROFILE_SCOPE("Layers Update");
                    for (Layer * l : layerStack)
                    {
                        l->onUpdate(ts);
                    }
                }

                imGuiLayer->begin();
                {
                    PROFILE_SCOPE("imGui Update");
                    for (Layer * l : layerStack)
                    {
                        l->onImGuiRender();
                    }
                }
                imGuiLayer->end();
            }

            // auto [x, y] = Input::getMousePos();
            // CORE_TRACE("{0}, {1}", x, y);
            window->onUpdate();
        }
    }

    void Application::onEvent(Event & e)
    {
        PROFILE_FUNCTION();
#ifdef LOG_EVENTS
        CORE_TRACE("{0}", e);
#endif // LOG_EVENTS
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT(Application::onClose));
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT(Application::resizeEvent));

        for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it)
        {
            (*it)->onEvent(e);
            if (e.handled)
            {
                break;
            }
        }
    }

    void Application::pushLayer(Layer * layer)
    {
        PROFILE_FUNCTION();
        layerStack.push(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer * overlay)
    {
        PROFILE_FUNCTION();
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::Quit()
    {
        PROFILE_FUNCTION();
        Application::Get().crashed = true;
    }

    bool Application::onClose(WindowCloseEvent & e)
    {
        PROFILE_FUNCTION();
        crashed = true;
        return true;
    }

    bool Application::resizeEvent(WindowResizeEvent & rse)
    {
        PROFILE_FUNCTION();
        if (rse.getWidth() == 0 || rse.getHeight() == 0)
        {
            minimised = true;
            return false;
        }
        minimised = false;

        Renderer::WindowResize(rse.getWidth(), rse.getHeight());

        return false;
    }
} // namespace OE
