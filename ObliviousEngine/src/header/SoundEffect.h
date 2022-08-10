#pragma once
#include <SDL_mixer.h>

//typedef void (SoundEffect::*fptr)();

class SoundEffect
{
public:
	SoundEffect(const char* fileName);
	~SoundEffect();

	Mix_Chunk* getEffect();
	void setChannel(int channel);
	int getChannel();
	bool isPlaying();
	void setPlaying(bool b);
	void end();

private:
	Mix_Chunk* effect;
	int channel;
	bool playing;
};
