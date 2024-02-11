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

        void push(Layer * layer);
        void pushOverlay(Layer * overlay);
        void pop(Layer * layer);
        void popOverlay(Layer * overlay);

        std::vector<Layer *>::iterator begin() { return layers.begin(); }
        std::vector<Layer *>::iterator end() { return layers.end(); }

    private:
        std::vector<Layer *> layers;
        unsigned int layerIndex = 0;
    };
} // namespace OE
