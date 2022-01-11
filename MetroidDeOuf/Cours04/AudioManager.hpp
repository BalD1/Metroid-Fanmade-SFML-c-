#pragma once
#include "stdafx.hpp"
class AudioManager
{
private:

	sf::Music			globalMusic;
	sf::Sound*			menuSound;

public:

	int musicVolume = 30;
	int sfxVolume = 100;

	int musicVolumeModifier = 5;
	int sfxVolumeModifier = 5;

	AudioManager();
	~AudioManager();

	void setMusic(const char* musicPath, int volume = -1);
	void changeMusicVolume(int volume);
	void stopMusic();

	void playSound(sf::SoundBuffer* s);
	void playSound(sf::SoundBuffer* s, sf::Sound* origin);

	void playWinMusic();

};

