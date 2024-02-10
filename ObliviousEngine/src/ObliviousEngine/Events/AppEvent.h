#pragma once
#include "ObliviousEngine/Events/Event.h"

namespace OE
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WinClose);
        EVENT_CLASS_CAT(ECApp);
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int w, int h) : width(w), height(h) {}

        inline int getWidth() const { return width; }
        inline int getHeight() const { return height; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Resize Event: " << width << ", " << height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WinResize);
        EVENT_CLASS_CAT(ECApp);

    private:
        int width, height;
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick);
        EVENT_CLASS_CAT(ECApp);
    };

    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate);
        EVENT_CLASS_CAT(ECApp);
    };

    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender);
        EVENT_CLASS_CAT(ECApp);
    };

} // namespace OE
