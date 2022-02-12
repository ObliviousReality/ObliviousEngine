#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
class Texture
{
public:
	Texture(SDL_Renderer* renderer);
	~Texture();

	bool loadFromFile(std::string path);
	void free();
	void render(int x, int y);
	int getHeight();
	int getWidth();

	SDL_Renderer* renderer;

protected:
	SDL_Texture* texture;
	
	int width;
	int height;
};

