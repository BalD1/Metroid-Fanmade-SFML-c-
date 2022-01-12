#pragma once
#include "stdafx.hpp"
#include "Bullet.hpp"
#include "World.hpp"
#include "AudioManager.hpp"
#include "Particles.hpp"

class Game;

class Weapon
{
private:

	Particles*						fireParticles = nullptr;

	sf::Sprite*						spr = nullptr;
	sf::Texture*					texture = nullptr;
	sf::Vector2f					offset = { 0,0 };

	std::vector<Bullet*>			bulletsPool;
	int								poolCount = 10;

	sf::Vector2i					pastMousePos;
	float							joystickSpeed = 10;

	int								damages = 20;

	float							CDtimer = 0;


	int								cx = 0;
	float							rx = 0;
	int								cy = 0;
	float							ry = 0;
	float							xx = 0;
	float							yy = 0;


public:

	World*							worldRef = nullptr;
	AudioManager*					audioManagerRef = nullptr;

	sf::SoundBuffer*				fireSound = nullptr;
	sf::Sound*						soundsOrigin = nullptr;

	Game*							gameRef = nullptr;

	sf::Vector2f					mousePosition;
	float							fireCD = 0.15f;
	int								stride = 32;

	int								knockbackForce = 1;

	bool							canFire = true;

	Weapon();
	~Weapon();

	void setPosition(int _cx, float _rx, int _cy, float _ry);
	void setAudiomanager(AudioManager* _audioManagerRef);
	void setOffset(sf::Vector2f _offset);
	void lookAtMouse();

	void fire();
	void setBullet(Bullet* bullet);
	void checkBulletCollision();

	void update(float dt);
	void render(sf::RenderTarget& target, sf::RenderStates states);
};

