#pragma once
#include "stdafx.hpp"
#include "Entity.hpp"
#include "Particles.hpp"
#include "AudioManager.hpp"

class Bullet : public Entity
{
private:

	sf::CircleShape*				spr = nullptr;

	sf::Vector2f					direction = { 1,0 };

	float							speed = 17;
	int								size = 4;

	bool							active = false;

	Particles*						hitParticles = nullptr;

public:

	AudioManager*					audioManagerRef = nullptr;
	sf::SoundBuffer*				wallHitSound = nullptr;
	sf::Sound*						soundOrigin = nullptr;

	Bullet(int _cx, int _cy, int stride, sf::Vector2f _direction = { 0,0 });
	~Bullet();

	void setPosition(int _cx, float _rx, int _cy, float _ry);
	void setDirection(sf::Vector2f dir);
	void manageMovements(float dt);
	void syncSprite(float dt);

	void createParticles();

	void playWallHitSound();

	bool isActive() { return active; }
	void setActive(bool _active);

	void update(float dt);
	void render(sf::RenderTarget& target);
};

