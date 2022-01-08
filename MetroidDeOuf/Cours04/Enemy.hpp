#pragma once
#include "Character.hpp"
#include "Game.hpp"

class Enemy : public Character
{
private:

	Game*				gameRef = nullptr;

	int					direction = 1;
	int					damages = 1;

public:

	Enemy(std::string _name, float _cx, float _cy, int _stride, sf::Texture& _texture);
	~Enemy();

	void setGame(Game* _gameRef);
	void manageMovements(float dt);
	bool isTouchingPlayer();

	void update(float dt);
};

