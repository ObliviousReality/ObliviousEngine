#pragma once
#include <ObliviousEngine/Core/Window.h>
#include <GLFW/glfw3.h>

namespace OE
{
	class WinWindow : public Window
	{
	private:
		struct WindowData
		{
			std::string name;
			int width, height;
			bool vsync;

			EventCallbackFn callback;
		};
		WindowData winProps;
	public:
		WinWindow(const Properties& props);
		virtual ~WinWindow();

		void onUpdate() override;

		inline int getWidth() const override { return winProps.width; }
		inline int getHeight() const override { return winProps.height; }

		inline void setEventCallback(const EventCallbackFn& callback) override { winProps.callback = callback; }

		void setVSync(bool e) override;
		bool vsynced() const override;

	private:
		virtual void init(const Properties& props);
		virtual void close();

		GLFWwindow* window;

		
		
	};
}