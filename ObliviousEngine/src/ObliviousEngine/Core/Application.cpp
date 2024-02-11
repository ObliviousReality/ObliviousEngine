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
        OE_PROFILE_FUNCTION();
        OE_CORE_ASSERT(!instance, "APPLICATION ALREADY EXISTS");
        instance = this;
        window = Window::WindowCreate(Properties("Sandbox!", 1920, 1080));
        window->setEventCallback(OE_BIND_EVENT(Application::onEvent));
        window->setVSync(true);

        Renderer::Init();

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);
    }

    Application::~Application()
    {
        OE_PROFILE_FUNCTION();
        Renderer::Finish();
    }

    void Application::run()
    {
        OE_PROFILE_FUNCTION();
        while (!crashed)
        {
            OE_PROFILE_SCOPE("Individual Run Loop");

            float time = (float)glfwGetTime(); // Platform specific
            Timestep ts = time - frameTime;
            frameTime = time;
            if (!minimised)
            {
                {
                    OE_PROFILE_SCOPE("Layers Update");
                    for (Layer * l : layerStack)
                    {
                        l->onUpdate(ts);
                    }
                }

                imGuiLayer->begin();
                {
                    OE_PROFILE_SCOPE("imGui Update");
                    for (Layer * l : layerStack)
                    {
                        l->onImGuiRender();
                    }
                }
                imGuiLayer->end();
            }

            // auto [x, y] = Input::getMousePos();
            // OE_CORE_TRACE("{0}, {1}", x, y);
            window->onUpdate();
        }
    }

    void Application::onEvent(Event & e)
    {
        OE_PROFILE_FUNCTION();
#ifdef LOG_EVENTS
        OE_CORE_TRACE("{0}", e);
#endif // LOG_EVENTS
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(OE_BIND_EVENT(Application::onClose));
        dispatcher.dispatch<WindowResizeEvent>(OE_BIND_EVENT(Application::resizeEvent));

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
        OE_PROFILE_FUNCTION();
        layerStack.push(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer * overlay)
    {
        OE_PROFILE_FUNCTION();
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::Quit()
    {
        OE_PROFILE_FUNCTION();
        Application::Get().crashed = true;
    }

    bool Application::onClose(WindowCloseEvent & e)
    {
        OE_PROFILE_FUNCTION();
        crashed = true;
        return true;
    }

    bool Application::resizeEvent(WindowResizeEvent & rse)
    {
        OE_PROFILE_FUNCTION();
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
