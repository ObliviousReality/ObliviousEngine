#include "..\..\header\Music.h"

Music::Music(const char* filename)
{
	music = Mix_LoadMUS(filename);
}

Music::~Music()
{
	Mix_FreeMusic(music);
}

Mix_Music* Music::getMusic()
{
	return music;
}
