#pragma once

#include "ObliviousEngine/Renderer/Layer.h"

#include "ObliviousEngine/Events/AppEvent.h"
#include "ObliviousEngine/Events/KeyEvent.h"
#include "ObliviousEngine/Events/MouseEvent.h"

namespace OE {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetatch() override;

		void begin();
		void end();

	private:
		float m_Time = 0.0f;
	};
}