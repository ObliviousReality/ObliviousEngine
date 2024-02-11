#include "oepch.h"

#include "ObliviousEngine/Renderer/LayerStack.h"

namespace OE
{
    LayerStack::~LayerStack()
    {
        for (Layer * l : layers)
        {
            l->onDetatch();
            delete l;
        }
    }

    void LayerStack::push(Layer * layer)
    {
        layers.emplace(layers.begin() + layerIndex, layer);
        layerIndex++;
    }

    void LayerStack::pushOverlay(Layer * overlay) { layers.emplace_back(overlay); }

    void LayerStack::pop(Layer * layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);
        if (it != layers.end())
        {
            layers.erase(it);
            layerIndex--;
            layer->onDetatch();
        }
    }

    void LayerStack::popOverlay(Layer * overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);
        if (it != layers.end())
        {
            layers.erase(it);
            overlay->onDetatch();
        }
    }
} // namespace OE
