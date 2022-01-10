#pragma once
#include "stdafx.hpp"
class AudioManager
{
private:

	sf::Music			globalMusic;
	sf::Sound*			menuSound;

public:

	float musicVolume = 05;

	AudioManager();
	~AudioManager();

	void setMusic(const char* musicPath, float volume = -1);
	void changeMusicVolume(float volume);

	void playSound(sf::SoundBuffer* s);
	void playSound(sf::SoundBuffer* s, sf::Sound* origin);

};

