#pragma once
#include <SDL_mixer.h>
class Music
{
public:
	Music(const char* filename);
	~Music();

	Mix_Music* getMusic();
private:
	Mix_Music* music;
};

