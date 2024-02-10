#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "ObliviousEngine/Core/Timestep.h"
#include "ObliviousEngine/imgui/ImGuiLayer.h"

#include <ObliviousEngine/Core/Window.h>
#include <ObliviousEngine/Events/AppEvent.h>
#include <ObliviousEngine/Events/Event.h>
#include <ObliviousEngine/Renderer/LayerStack.h>

namespace OE
{

    class Application
    {
    public:
        Application();
        virtual ~Application();
        static void Init(); // SDL
        static void Quit();
        void run();
        virtual void loop();

        void onEvent(Event & e);

        void pushLayer(Layer * l);
        void pushOverlay(Layer * l);

        inline static Application & Get() { return *instance; }
        inline Window & getWindow() { return *window; }

    private:
        bool onClose(WindowCloseEvent & e);
        bool resizeEvent(WindowResizeEvent & rse);

    private:
        std::unique_ptr<Window> window;
        ImGuiLayer * imGuiLayer;
        bool crashed = false;
        bool minimised = false;
        LayerStack ls;
        float frameTime = 0.0f;

    private:
        static Application * instance;
    };

    // Client side
    Application * CreateApplication();

} // namespace OE

#endif // !APPLICATION_H
