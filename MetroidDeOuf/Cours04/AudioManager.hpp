#pragma once
#include "stdafx.hpp"
class AudioManager
{
private:

	sf::Music globalMusic;

public:

	float musicVolume = 50;

	AudioManager();
	~AudioManager();

	void setMusic(const char* musicPath, float volume = -1);
	void changeMusicVolume(float volume);

};

