#pragma once
#include <ObliviousEngine/Core/Window.h>
#include "ObliviousEngine/Renderer/RenderContext.h"
#include <GLFW/glfw3.h>


namespace OE
{
	class OBLIVIOUSENGINE_API WinWindow : public Window
	{

	public:
		WinWindow(const Properties& props);
		virtual ~WinWindow();

		void onUpdate() override;

		inline int getWidth() const override { return winProps.width; }
		inline int getHeight() const override { return winProps.height; }

		inline void setEventCallback(const EventCallbackFn& callback) override { winProps.callback = callback; }

		void setVSync(bool e) override;
		bool vsynced() const override;

		inline virtual void* getNativeWindow() const { return window; }
	private:
		virtual void init(const Properties& props);
		virtual void close();
	private:

		GLFWwindow* window;

		RenderContext* context;

		struct WindowData
		{
			std::string name;
			int width, height;
			bool vsync;

			EventCallbackFn callback;
		};
		WindowData winProps;


	};
}