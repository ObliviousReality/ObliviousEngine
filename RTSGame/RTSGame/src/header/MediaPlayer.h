#pragma once
#include <SDL_mixer.h>
#include<iostream>
#include "SoundEffect.h"
#include "Music.h"
class MediaPlayer
{
public:
	static void playRawEffect(Mix_Chunk* effect, int loops);
	static void playRawMusic(Mix_Music* music, int loops);
	static void playEffect(SoundEffect* effect, int loops);
	static void playMusic(Music* music, int loops);
	static void pause();
	static void play();
	static void stop();
	static void setGlobalVolume(int vol);

	static void pauseEffect(SoundEffect* effect);
	static void resumeEffect(SoundEffect* effect);
	static void stopEffect(SoundEffect* effect);
	static void setEffectVolume(SoundEffect* effect, int volume);

};

