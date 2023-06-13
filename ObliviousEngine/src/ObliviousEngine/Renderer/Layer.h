#pragma once
#include "Core.h"
#include <ObliviousEngine/Events/Event.h>

namespace OE
{
	class OBLIVIOUSENGINE_API Layer
	{
	public:
		Layer(const std::string& n = "Layer!");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetatch() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return name; }

	protected:
		std::string name;
		bool enabled = true;
	};
}