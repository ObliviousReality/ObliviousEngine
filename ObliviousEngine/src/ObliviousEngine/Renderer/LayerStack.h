#pragma once

#include "Core.h"

#include "Layer.h"

namespace OE
{
	class OBLIVIOUSENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void push(Layer* l);
		void pushOverlay(Layer* ov);
		void pop(Layer* l);
		void popOverlay(Layer* ov);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerIn;
	};
}