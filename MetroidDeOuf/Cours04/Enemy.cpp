#include "Enemy.hpp"

Enemy::Enemy(std::string _name, float _cx, float _cy, int _stride, sf::Texture& _texture)
	:Character(_name, _cx, _cy, _stride)
{
	this->texture = &_texture;
	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);
	syncSprite(1);

	this->speed = 3;
	dx = speed;
	this->invincibility_CD = 0.1f;			// keep the inv timer low but not 0
}

Enemy::~Enemy()
{
}

void Enemy::setGame(Game* _gameRef)
{
	this->gameRef = _gameRef;
}

void Enemy::manageMovements(float dt)
{
	// x
	rx += dx * dt;

	if (isCollidingWithWorld(cx - 1, cy) && rx <= 0.01f)
	{
		rx = 0.01f;
		dx *= -1;
	}
	if ((isCollidingWithWorld(cx + 1, cy) && rx >= 0.99f) || (isCollidingWithWorld(cx + 2, cy) && rx >= 0.99f))
	{
		rx = 0.99f;
		dx *= -1;
	}

	while (rx > 1) { rx--; cx++; }
	while (rx < 0) { rx++; cx--; }

	// y
	ry += dy * dt;
	dy *= frict_y * dt;

	if ((isCollidingWithWorld(cx, cy - 1) && ry <= 0.01f) || (isCollidingWithWorld(cx + 1, cy - 1) && ry <= 0.01f))
	{
		ry = 0.01f;
		dy = 0;
	}
	if ((isCollidingWithWorld(cx, cy + 1) && ry >= 0.01f) || (isCollidingWithWorld(cx + 1, cy + 1) && ry >= 0.01f))
	{
		ry = 0.01f;
		dy = 0;
	}

	while (ry > 1) { ry--; cy++; }
	while (ry < 0) { ry++; cy--; }

	isTouchingPlayer();

	syncSprite(dt);
}

bool Enemy::isTouchingPlayer()
{
	if (isCollidingSelf(gameRef->player->cx, gameRef->player->cy))
	{
		gameRef->player->takeDamages(this->damages);
		return true;
	}
	return false;
}

void Enemy::update(float dt)
{
	if (!ignoreGravity)
	{
		applyGravity(dt);
		manageMovements(dt);
	}
	manageState();
}
