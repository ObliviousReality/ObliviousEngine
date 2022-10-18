#include "oepch.h"
#include "LayerStack.h"

namespace OE
{
	LayerStack::LayerStack()
	{
		layerIn = layers.begin();
	}
	LayerStack::~LayerStack()
	{
		for (Layer* l : layers)
		{
			delete l;
		}
	}
	void LayerStack::push(Layer* l)
	{
		layerIn = layers.emplace(layerIn, l);
	}
	void LayerStack::pushOverlay(Layer* ov)
	{
		layers.emplace_back(ov);
	}
	void LayerStack::pop(Layer* l)
	{
		auto it = std::find(layers.begin(), layers.end(), l);
		if (it != layers.end())
		{
			layers.erase(it);
			layerIn--;
		}
	}
	void LayerStack::popOverlay(Layer* ov)
	{
		auto it = std::find(layers.begin(), layers.end(), ov);
		if (it != layers.end())
		{
			layers.erase(it);
		}
	}
}