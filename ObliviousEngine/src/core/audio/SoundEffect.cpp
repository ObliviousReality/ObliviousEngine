#include "pch.h"
#include "..\..\header\SoundEffect.h"
#include <stdio.h>
#include <functional>

SoundEffect::SoundEffect(const char* fileName)
{
	effect = Mix_LoadWAV(fileName);
	if (effect == NULL)
	{
		printf("Error: %s\n", Mix_GetError());
	}
	channel = -1;
	playing = false;
	//hook = &SoundEffect::end;
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

bool SoundEffect::isPlaying()
{
	return playing;
}

void SoundEffect::setPlaying(bool b)
{
	playing = b;
}

void SoundEffect::end()
{
}

