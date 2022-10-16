#pragma once
#include "Core.h"
//#include "Texture.h"
#include <SDL_ttf.h>

namespace OE {
    class OBLIVIOUSENGINE_API Text 
    {
    public:
        Text();
        ~Text();
        bool loadText(std::string text, SDL_Colour textColour, TTF_Font* font);
        void free();
        int getHeight() { return height; }
        int getWidth() { return width; }

    private:
        SDL_Texture* texture;

        int width;
        int height;
    };

}