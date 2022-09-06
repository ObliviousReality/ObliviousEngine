#pragma once
#include "Core.h"
#include "Texture.h"
#include <SDL_ttf.h>

namespace OE {

    class OBLIVIOUSENGINE_API Text :
        public Texture
    {
    public:
        Text(Renderer* renderer);
        ~Text();
        bool loadText(std::string text, SDL_Colour textColour, TTF_Font* font);
    };

}