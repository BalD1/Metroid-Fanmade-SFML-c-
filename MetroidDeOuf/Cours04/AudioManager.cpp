#include "AudioManager.hpp"

AudioManager::AudioManager()
{
	menuSound = new sf::Sound();
	menuSound->setVolume(sfxVolume);
}

AudioManager::~AudioManager()
{
	delete(menuSound);
}

void AudioManager::setMusic(const char* musicPath, int volume)
{
	if (!globalMusic.openFromFile(musicPath))
	{
		std::cout << "Could not load main music";
		return;
	}
	if (volume >= 0)
		musicVolume = volume;

	globalMusic.setVolume(musicVolume);
	globalMusic.setLoop(true);
	globalMusic.play();
}

void AudioManager::changeMusicVolume(int volume)
{
	globalMusic.setVolume(volume);
	musicVolume = volume;
}

void AudioManager::stopMusic()
{
	globalMusic.stop();
}

void AudioManager::playSound(sf::SoundBuffer* s)
{
	menuSound->setVolume(sfxVolume);
	menuSound->setPosition(sf::Listener::getPosition());
	menuSound->setBuffer(*s);
	menuSound->play();
}

void AudioManager::playSound(sf::SoundBuffer* s, sf::Sound* origin)
{
	if (!origin->isRelativeToListener())
		origin->setPosition(sf::Listener::getPosition());
	origin->setVolume(sfxVolume);
	origin->setBuffer(*s);
	origin->play();
}

void AudioManager::playWinMusic()
{
	if (!globalMusic.openFromFile("Assets/Sounds/winmusic.ogg"))
	{
		std::cout << "Could not load win music from Assets/Sounds/winmusic.ogg";
		return;
	}
	globalMusic.setLoop(false);
	globalMusic.play();
}
