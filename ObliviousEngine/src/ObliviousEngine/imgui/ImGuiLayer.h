#pragma once

#include "ObliviousEngine/Renderer/Layer.h"

#include "ObliviousEngine/Events/AppEvent.h"
#include "ObliviousEngine/Events/KeyEvent.h"
#include "ObliviousEngine/Events/MouseEvent.h"

namespace OE {

	class OBLIVIOUSENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetatch();
		void onUpdate();
		void onEvent(Event& event);
	private:
		bool onMouseDownEvent(MouseDownEvent& e);
		bool onMouseUpEvent(MouseUpEvent& e);

		bool onMouseMoveEvent(MouseMoveEvent& e);
		bool onMouseScrollEvent(MouseScrollEvent& e);

		bool onKeyDownEvent(KeyDownEvent& e);
		bool onKeyUpEvent(KeyUpEvent& e);

		//bool onKeyTypeEvent(KeyTypeEvent& e);

		bool onWindowResizeEvent(WindowResizeEvent& e);


	private:
		float m_Time = 0.0f;
	};
}