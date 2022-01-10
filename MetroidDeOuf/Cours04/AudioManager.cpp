#include "AudioManager.hpp"

AudioManager::AudioManager()
{
	menuSound = new sf::Sound();
	menuSound->setVolume(100);
}

AudioManager::~AudioManager()
{
	delete(menuSound);
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

void AudioManager::playSound(sf::SoundBuffer* s)
{
	menuSound->setPosition(sf::Listener::getPosition());
	menuSound->setBuffer(*s);
	menuSound->play();
}

void AudioManager::playSound(sf::SoundBuffer* s, sf::Sound* origin)
{
	if (!origin->isRelativeToListener())
		origin->setPosition(sf::Listener::getPosition());
	origin->setBuffer(*s);
	origin->play();
}
