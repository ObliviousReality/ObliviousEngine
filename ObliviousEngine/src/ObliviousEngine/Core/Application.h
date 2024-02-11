#pragma once

#include "Core.h"
#include "Timestep.h"
#include "Window.h"

#include "ObliviousEngine/Events/AppEvent.h"
#include "ObliviousEngine/Events/Event.h"

#include "ObliviousEngine/imgui/ImGuiLayer.h"

#include "ObliviousEngine/Renderer/LayerStack.h"

int main(int argc, char ** argv);

namespace OE
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        static void Quit();

        void onEvent(Event & e);

        void pushLayer(Layer * layer);
        void pushOverlay(Layer * overlay);

        inline static Application & Get() { return *instance; }
        inline Window & getWindow() { return *window; }

    private:
        void run();

        bool onClose(WindowCloseEvent & e);
        bool resizeEvent(WindowResizeEvent & rse);

    private:
        std::unique_ptr<Window> window;
        ImGuiLayer * imGuiLayer;
        bool crashed = false;
        bool minimised = false;
        LayerStack layerStack;
        float frameTime = 0.0f;

    private:
        static Application * instance;

        friend int ::main(int argc, char ** argv);
    };

    // Client side
    Application * CreateApplication();

} // namespace OE
