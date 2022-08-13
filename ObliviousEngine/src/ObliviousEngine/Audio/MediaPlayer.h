#pragma once
#include <SDL_mixer.h>

#include "SoundEffect.h"
#include "Music.h"
#include "Core.h"

namespace OE {

	class OBLIVIOUSENGINE_API MediaPlayer
	{
	public:
		static void playRawEffect(Mix_Chunk* effect, int loops = 0);
		static void playRawMusic(Mix_Music* music, int loops = 0);
		static void playEffect(SoundEffect* effect, int loops = 0);
		static void playMusic(Music* music, int loops = 0);
		static void pause();
		static void play();
		static void stop();
		static void setGlobalVolume(int vol);

		static void pauseEffect(SoundEffect* effect);
		static void resumeEffect(SoundEffect* effect);
		static void stopEffect(SoundEffect* effect);
		static void globalStop();
		static void globalPause();
		static void globalPlay();
		static void setEffectVolume(SoundEffect* effect, int volume);

		static int setMixerChannels(int num);

	private:
		static void effectEnded(int channel);
		static void musicEnded();

	};

}