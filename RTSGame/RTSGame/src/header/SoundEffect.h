#pragma once
#include <SDL_mixer.h>
class SoundEffect
{
public:
	SoundEffect(const char* fileName);
	~SoundEffect();

	Mix_Chunk* getEffect();
	void setChannel(int channel);
	int getChannel();

private:
	Mix_Chunk* effect;
	int channel;

};

