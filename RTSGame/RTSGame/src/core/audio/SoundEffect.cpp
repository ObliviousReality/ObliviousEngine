#include "..\..\header\SoundEffect.h"

SoundEffect::SoundEffect(const char* fileName)
{
	effect = Mix_LoadWAV(fileName);
	channel = -1;
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(effect);
}

Mix_Chunk* SoundEffect::getEffect()
{
	return effect;
}

void SoundEffect::setChannel(int channel)
{
	this->channel = channel;
}

int SoundEffect::getChannel()
{
	return channel;
}

