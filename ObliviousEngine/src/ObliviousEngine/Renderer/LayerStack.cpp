#include "oepch.h"
#include "ObliviousEngine/Renderer/LayerStack.h"

namespace OE
{
	LayerStack::~LayerStack()
	{
		for (Layer* l : layers)
		{
			l->onDetatch();
			delete l;
		}
	}
	void LayerStack::push(Layer* l)
	{
		layers.emplace(layers.begin() + layerIndex, l);
		layerIndex++;
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
			layerIndex--;
			l->onDetatch();
		}
	}
	void LayerStack::popOverlay(Layer* ov)
	{
		auto it = std::find(layers.begin(), layers.end(), ov);
		if (it != layers.end())
		{
			layers.erase(it);
			ov->onDetatch();
		}
	}
}