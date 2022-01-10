#pragma once
#include "Character.hpp"
#include "Player.hpp"
#include "Particles.hpp"

class Enemy : public Character
{
private:

	Player*				playerRef = nullptr;
	Particles*			hitParticles = nullptr;

	int					direction = 1;
	int					damages = 10;

	sf::SoundBuffer*	enemyKill = nullptr;
	sf::SoundBuffer*	enemyHurt = nullptr;

	float				delayedDestroy_CD = 1;
	float				delayedDestroy_TIMER = 1;

	int					knockBackForce = 25;

public:

	Enemy(std::string _name, float _cx, float _cy, int _stride, sf::Texture& _texture);
	~Enemy();

	void setPlayer(Player* _playerRef);
	void manageMovements(float dt);
	bool isTouchingPlayer();

	void takeDamages(float rawDamages, int otherXX = 0, int otherYY = 0, int _knockbackForce = 0);

	void update(float dt);
	void render(sf::RenderTarget& target);

	bool canDestroy() { return delayedDestroy_TIMER <= 0; };
};

