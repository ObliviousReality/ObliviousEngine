#pragma once

#include "Core.h"

#include "Layer.h"

namespace OE
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void push(Layer* l);
		void pushOverlay(Layer* ov);
		void pop(Layer* l);
		void popOverlay(Layer* ov);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	private:
		std::vector<Layer*> layers;
		unsigned int layerIndex = 0;
	};
}