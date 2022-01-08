#include "AudioManager.hpp"

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::setMusic(const char* musicPath, float volume)
{
	if (!globalMusic.openFromFile(musicPath))
	{
		std::cout << "Could not load main music";
		return;
	}
	if (volume < 0)
		volume = musicVolume;
	else
		musicVolume = volume;

	globalMusic.setVolume(volume);
	globalMusic.setLoop(true);
	globalMusic.play();
}

void AudioManager::changeMusicVolume(float volume)
{
	globalMusic.setVolume(volume);
	musicVolume = volume;
}
