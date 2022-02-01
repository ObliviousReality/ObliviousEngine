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
	bool isPlaying();
	void setPlaying(bool b);
	void end();
	void* getHook();

private:
	Mix_Chunk* effect;
	int channel;
	bool playing;
	void (SoundEffect::*hook)();
};

