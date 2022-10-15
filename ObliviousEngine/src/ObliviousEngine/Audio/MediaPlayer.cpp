#include "oepch.h"
#include "MediaPlayer.h"
#include <ObliviousEngine/Core/Log.h>

namespace OE {

	void MediaPlayer::playRawEffect(Mix_Chunk* effect, int loops)
	{
		int channel = Mix_PlayChannel(-1, effect, loops);
		printf("Channel: %i\n", channel);
		Mix_ChannelFinished(MediaPlayer::effectEnded);
	}

	void MediaPlayer::playRawMusic(Mix_Music* music, int loops)
	{
		Mix_PlayMusic(music, loops);
		Mix_HookMusicFinished(MediaPlayer::musicEnded);
	}

	void MediaPlayer::playEffect(SoundEffect* effect, int loops)
	{
		int channel = Mix_PlayChannel(-1, effect->getEffect(), loops);
		effect->setChannel(channel);
		effect->setPlaying(true);
		printf("Channel %i assigned.\n", channel);
		if (channel == -1)
		{
			printf("Error: %s\n", Mix_GetError());
		}
	}

	void MediaPlayer::playMusic(Music* music, int loops)
	{
		Mix_PlayMusic(music->getMusic(), loops);
	}

	void MediaPlayer::pause()
	{
		Mix_PauseMusic();
	}

	void MediaPlayer::play()
	{
		Mix_ResumeMusic();
	}

	void MediaPlayer::stop()
	{
		Mix_HaltMusic();
	}

	void MediaPlayer::setGlobalVolume(int vol)
	{
		Mix_Volume(-1, vol);
		Mix_VolumeMusic(vol);
	}

	void MediaPlayer::pauseEffect(SoundEffect* effect)
	{
		int channel = effect->getChannel();
		if (Mix_Playing(channel) == 1)
		{
			Mix_Pause(channel);
			effect->setPlaying(false);
		}
	}

	void MediaPlayer::resumeEffect(SoundEffect* effect)
	{
		int channel = effect->getChannel();
		if (Mix_Playing(channel) == 0)
		{
			Mix_Resume(channel);
			effect->setPlaying(false);
		}
	}

	void MediaPlayer::stopEffect(SoundEffect* effect)
	{
		int channel = effect->getChannel();
		Mix_HaltChannel(channel);
		effect->setPlaying(false);
	}

	void MediaPlayer::globalStop()
	{
		MediaPlayer::stop();
		//for Mix_channels
	}

	void MediaPlayer::globalPause()
	{
	}

	void MediaPlayer::globalPlay()
	{
	}

	void MediaPlayer::setEffectVolume(SoundEffect* effect, int volume)
	{
		if (effect->isPlaying())
		{
			Mix_Volume(effect->getChannel(), volume);
		}
	}

	int MediaPlayer::setMixerChannels(int num)
	{
		OE_CORE_INFO("{}", MIX_CHANNELS);
		return Mix_AllocateChannels(16);
	}

	void MediaPlayer::effectEnded(int channel)
	{
		printf("Channel %i Ended\n", channel);
	}

	void MediaPlayer::musicEnded()
	{
	}

}