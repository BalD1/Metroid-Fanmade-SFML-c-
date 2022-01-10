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

	sf::RectangleShape*				spr = nullptr;
	sf::Vector2f					offset = { 0,0 };

	std::vector<Bullet*>			bulletsPool;
	int								poolCount = 10;

	sf::Vector2i					pastMousePos;
	float							joystickSpeed = 10;

	int								damages = 30;

	float							CDtimer = 0;

	float							cx;
	float							rx;
	float							cy;
	float							ry;
	float							xx;
	float							yy;


public:

	World*							worldRef = nullptr;
	AudioManager*					audioManagerRef = nullptr;

	sf::SoundBuffer*				fireSound = nullptr;
	sf::Sound*						soundsOrigin = nullptr;

	Game*							gameRef = nullptr;

	sf::Vector2f					mousePosition;
	float							fireCD = 0.2f;
	int								stride = 32;

	int								knockbackForce = 1;

	Weapon();
	~Weapon();

	void setPosition(float _cx, float _rx, float _cy, float _ry);
	void setOffset(sf::Vector2f _offset);
	void lookAtMouse();

	void fire();
	void setBullet(Bullet* bullet);
	void checkBulletCollision();

	void update(float dt);
	void render(sf::RenderTarget& target, sf::RenderStates states);
};

