#pragma once
#include "Event.h"

namespace OE
{
	class OBLIVIOUSENGINE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WinClose);
		EVENT_CLASS_CAT(ECApp);
	};

	class OBLIVIOUSENGINE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int w, int h)
			: width(w), height(h) {}

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

	class OBLIVIOUSENGINE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CAT(ECApp);
	};
	
	class OBLIVIOUSENGINE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CAT(ECApp);
	}; 
	
	class OBLIVIOUSENGINE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CAT(ECApp);
	};

}