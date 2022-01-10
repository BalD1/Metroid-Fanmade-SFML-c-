#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "AudioManager.hpp"

class Bullet : public Entity
{
private:

	sf::CircleShape*				spr = nullptr;

	sf::Vector2f					direction = { 1,0 };

	float							speed = 15;

	bool							active = false;

public:

	AudioManager*					audioManagerRef = nullptr;
	sf::SoundBuffer*				wallHitSound = nullptr;
	sf::Sound*						soundOrigin = nullptr;

	Bullet(float _cx, float _cy, int stride, float _size, float _speed, sf::Vector2f _direction = { 0,0 });
	~Bullet();

	void setPosition(float _cx, float _rx, float _cy, float _ry);
	void setDirection(sf::Vector2f dir);
	void manageMovements(float dt);
	void syncSprite(float dt);

	void playWallHitSound();

	bool isActive() { return active; }
	void setActive(bool _active);

	void update(float dt);
	void render(sf::RenderTarget& target);
};

