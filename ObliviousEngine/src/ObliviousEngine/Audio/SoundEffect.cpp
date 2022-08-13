#include "oepch.h"
#include "SoundEffect.h"

namespace OE {

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
		if (Mix_Playing(channel) == 1) {
			return true;
		}
		else {
			playing = false;
			return false;
		}
	}

	void SoundEffect::setPlaying(bool b)
	{
		playing = b;
	}

	void SoundEffect::end()
	{
	}

}