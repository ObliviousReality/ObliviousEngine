#include "..\header\MediaPlayer.h"

void MediaPlayer::playRawEffect(Mix_Chunk* effect, int loops)
{
	int channel = Mix_PlayChannel(-1, effect, loops);
	printf("Channel: %i\n", channel);
}

void MediaPlayer::playRawMusic(Mix_Music* music, int loops)
{
	Mix_PlayMusic(music, loops);
}

void MediaPlayer::playEffect(SoundEffect* effect, int loops)
{
	int channel = Mix_PlayChannel(-1, effect->getEffect(), loops);
	effect->setChannel(channel);
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
	}
}

void MediaPlayer::resumeEffect(SoundEffect* effect)
{
	int channel = effect->getChannel();
	if (Mix_Playing(channel) == 0)
	{
		Mix_Resume(channel);
	}
}

void MediaPlayer::stopEffect(SoundEffect* effect)
{
	int channel = effect->getChannel();
	if (Mix_Playing(channel) == 0)
	{
		Mix_HaltChannel(channel);
	}
}

void MediaPlayer::setEffectVolume(SoundEffect* effect, int volume)
{
	Mix_Volume(effect->getChannel(), volume);
}
