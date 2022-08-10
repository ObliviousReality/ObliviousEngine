#pragma once
#include "Texture.h"
#include <SDL_ttf.h>
class Text :
    public Texture
{
public:
    Text(SDL_Renderer* renderer);
    ~Text();
    bool loadText(std::string text, SDL_Colour textColour, TTF_Font* font);
};

