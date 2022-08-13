#pragma once
#include <SDL_mixer.h>
#include "Core.h"

//typedef void (SoundEffect::*fptr)();

namespace OE {

	class OBLIVIOUSENGINE_API SoundEffect
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

}