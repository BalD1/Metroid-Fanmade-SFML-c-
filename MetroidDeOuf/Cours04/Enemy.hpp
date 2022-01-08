#pragma once
#include "Character.hpp"
#include "Player.hpp"

class Enemy : public Character
{
private:

	Player*				playerRef = nullptr;

	int					direction = 1;
	int					damages = 1;

public:

	Enemy(std::string _name, float _cx, float _cy, int _stride, sf::Texture& _texture);
	~Enemy();

	void setPlayer(Player* _playerRef);
	void manageMovements(float dt);
	bool isTouchingPlayer();

	void update(float dt);
};

