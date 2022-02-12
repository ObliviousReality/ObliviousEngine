#include "..\..\header\Music.h"

Music::Music(const char* filename)
{
	music = Mix_LoadMUS(filename);
	playing = false;
}

Music::~Music()
{
	Mix_FreeMusic(music);
}

Mix_Music* Music::getMusic()
{
	return music;
}

bool Music::getPlaying()
{
	return playing;
}

void Music::setPlaying(bool b)
{
	playing = b;
}
