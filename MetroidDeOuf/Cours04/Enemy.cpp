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

	characterSoundPlayer->setRelativeToListener(true);

	enemyKill = new sf::SoundBuffer();
	if (!enemyKill->loadFromFile("Assets/Sounds/enemykill.wav"))
		printf("Enemy kill sound could not be loaded from Assets/Sounds/enemykill.wav");
	enemyHurt = new sf::SoundBuffer();
	if (!enemyHurt->loadFromFile("Assets/Sounds/enemyhurt.wav"))
		printf("Enemy hurt sound could not be loaded from Assets/Sounds/enemyhurt.wav");

	hitParticles = new Particles(sf::Color::Red, 2);
	delayedDestroy_TIMER = delayedDestroy_CD;
}

Enemy::~Enemy()
{
	delete(enemyKill);
	delete(enemyHurt);
	delete(hitParticles);
}

void Enemy::setPlayer(Player* _playerRef)
{
	this->playerRef = _playerRef;
}

void Enemy::manageMovements(float dt)
{
	// x
	if (dx != -speed && dx != speed)
	{
		if (knockback_TIMER <= 0)
		{
			if (dx < 0)
				dx = -speed;
			if (dx > 0)
				dx = speed;
		}
	}

	rx += dx * dt;

	if (isCollidingWithWorld(cx - 1, cy) && rx <= 0.01f || !isCollidingWithWorld(cx - 1, cy + 1) && rx <= 0.01f)
	{
		rx = 0.01f;
		dx *= -1;
	}
	if ((isCollidingWithWorld(cx + 1, cy) && rx >= 0.99f) || (isCollidingWithWorld(cx + 2, cy) && rx >= 0.99f) ||
		!isCollidingWithWorld(cx + 1, cy + 1) && rx >= 0.99f || !isCollidingWithWorld(cx + 2, cy + 1) && rx >= 0.99f)
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
	if (isCollidingSelf(playerRef->cx, playerRef->cy))
	{
		playerRef->takeDamages(this->damages, this->xx, this->yy, knockBackForce);
		return true;
	}
	return false;
}

void Enemy::takeDamages(float rawDamages, int otherXX, int otherYY, int _knockbackForce)
{
	if (invincibility_Timer <= 0)
	{
		Character::takeDamages(rawDamages);
		if (currentHealth > 0)
		{
			audioManagerRef->playSound(enemyHurt, characterSoundPlayer);
			hitParticles->create(xx, yy, 100, 100, 1, 5);
			knockBack(otherXX, otherYY, _knockbackForce);
		}
		else
		{
			audioManagerRef->playSound(enemyKill, characterSoundPlayer);
			hitParticles->create(xx, yy, 100, 100, 1, 10);
		}
	}
}

void Enemy::update(float dt)
{
	hitParticles->update(dt);
	if (alive())
	{
		if (invincibility_Timer > 0)
			invincibility_Timer -= dt;

		knockback_TIMER -= dt;

		if (!ignoreGravity)
		{
			applyGravity(dt);
			manageMovements(dt);
		}
		manageState();
	}
	else
		delayedDestroy_TIMER -= dt;
}

void Enemy::render(sf::RenderTarget& target)
{
	hitParticles->render(target);
	if (alive())
		Character::render(target);
}
