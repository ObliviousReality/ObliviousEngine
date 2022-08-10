#pragma once
#include <SDL_mixer.h>
class Music
{
public:
	Music(const char* filename);
	~Music();

	Mix_Music* getMusic();
	bool getPlaying();
	void setPlaying(bool b);
private:
	Mix_Music* music;
	bool playing;
};

