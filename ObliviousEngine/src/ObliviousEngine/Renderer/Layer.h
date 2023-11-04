#pragma once
#include "Core.h"
#include "ObliviousEngine/Events/Event.h"
#include "ObliviousEngine/Core/Timestep.h"

namespace OE
{
	class Layer
	{
	public:
		Layer(const std::string& n = "Layer!");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetatch() {}
		virtual void onUpdate(Timestep ts) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return name; }

	protected:
		std::string name;
		bool enabled = true;
	};
}