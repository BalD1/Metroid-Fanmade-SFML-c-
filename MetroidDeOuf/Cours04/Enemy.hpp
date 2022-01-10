#pragma once
#include "Character.hpp"
#include "Player.hpp"

class Enemy : public Character
{
private:

	Player*				playerRef = nullptr;

	int					direction = 1;
	int					damages = 10;

	sf::SoundBuffer*	enemyKill = nullptr;
	sf::SoundBuffer*	enemyHurt = nullptr;

public:

	Enemy(std::string _name, float _cx, float _cy, int _stride, sf::Texture& _texture);
	~Enemy();

	void setPlayer(Player* _playerRef);
	void manageMovements(float dt);
	bool isTouchingPlayer();

	void takeDamages(float rawDamages);

	void update(float dt);
};

