#pragma once
#include "oepch.h"

#include "Core.h"
#include <ObliviousEngine/Events/Event.h>

namespace OE
{

	struct Properties
	{
		std::string name;
		int width;
		int height;
		Properties(const std::string& n = "Window", int w = 1920, int h = 1080)
			: name(n), width(w), height(h)
		{}
	};

	class OBLIVIOUSENGINE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool vs) = 0;
		virtual bool vsynced() const = 0;

		static Window* createWindow(const Properties& props = Properties());
	};
}