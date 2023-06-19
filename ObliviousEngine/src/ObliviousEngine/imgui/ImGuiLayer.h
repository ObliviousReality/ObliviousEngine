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

		virtual void onAttach() override;
		virtual void onDetatch() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();

	private:
		float m_Time = 0.0f;
	};
}