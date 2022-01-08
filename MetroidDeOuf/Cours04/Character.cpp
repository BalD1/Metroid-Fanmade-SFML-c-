#include "Character.hpp"

Character::Character(std::string _name, float _cx, float _cy, int _stride) :
	Entity(_cx, _cy, _stride)
{
	this->name = _name;
}

Character::Character(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride) :
	Entity(_cx, _cy, _stride)
{
	this->name = _name;
	this->speed = _speed;
	this->invincibility_CD = _invicibilityCD;
	this->maxHealth = this->currentHealth = _maxHealth;
}

Character::~Character()
{
}

void Character::setGravity(float _gravity, bool _ignoreGravity)
{
	this->ignoreGravity = _ignoreGravity;
}

void Character::setWorld(World* _worldRef)
{
	this->worldRef = _worldRef;
}


bool Character::isCollidingWithWorld(float _cx, float _cy)
{
	if (_cx <= 0)
		return true;
	if (_cy <= 0)
		return true;
	if (_cx >= 1280 / stride)
		return true;
	if (_cy >= 960 / stride)
		return true;

	if (worldRef != nullptr)
	{
		for (size_t i = 0; i < worldRef->entities.size(); ++i)
		{
			if (worldRef->entities[i]->cx == _cx && worldRef->entities[i]->cy == _cy)
				return true;
		}
		std::printf("yo");
	}	

	return false;
}

bool Character::isCollidingSelf(float _cx, float _cy)
{
	if (cx == _cx && cy == _cy)
		return true;
	return false;
}

void Character::manageMovements(float dt)
{
	// x
	rx += dx * dt;
	dx *= frct_x * dt;

	if (isCollidingWithWorld(cx - 1, cy) && rx <= 0.01f)
	{
		rx = 0.01f;
		dx = 0;
	}
	if ((isCollidingWithWorld(cx + 1, cy) && rx >= 0.99f) || (isCollidingWithWorld(cx + 2, cy) && rx >= 0.99f))
	{
		rx = 0.99f;
		dx = 0;
	}

	while (rx > 1) { rx--; cx++; }
	while (rx < 0) { rx++; cx--; }

	// y
	ry += dy * dt;
	dy *= frict_y * dt;

	if ((isCollidingWithWorld(cx, cy -1) && ry <= 0.01f) || (isCollidingWithWorld(cx + 1, cy - 1) && ry <= 0.01f))
	{
		ry = 0.01f;
		dy = 0;
	}
	if ((isCollidingWithWorld(cx, cy + 1) && ry >= 0.01f) || (isCollidingWithWorld(cx + 1, cy + 1) && ry >= 0.01f) )
	{
		ry = 0.01f;
		dy = 0;
	}

	while (ry > 1) { ry--; cy++; }
	while (ry < 0) { ry++; cy--; }

	syncTransform();
}

void Character::applyGravity(float dt)
{
	isGrounded = (isCollidingWithWorld(cx, cy + 1) || isCollidingWithWorld(cx + 1, cy + 1));
	if (ignoreGravity || isGrounded || characterState == State::Jumping)
	{
		fallingSpeed = 0;
		return;
	}
	fallingSpeed += clamp(worldRef->gravity * mass * fallingSpeedFactor * dt, 0, maxFallingSpeed);
	dy += fallingSpeed;
}

void Character::manageState()
{
	characterState = State::Idle;
	if ((dx > 0.01f || dx < -0.01f) && characterState == State::Idle)
		characterState = State::Walking;
	if (dy > 0.01f)
		characterState = State::Falling;
	else if (dy < -0.01f)
		characterState = State::Jumping;

	moved = (!characterState == State::Idle);
}

void Character::syncTransform()
{
	xx = (cx + rx) * stride;
	yy = (cy + ry) * stride;
	this->setPosition(xx, yy);
}

void Character::takeDamages(float rawDamages)
{
	if (invincibility_Timer <= 0)
	{
		this->currentHealth -= rawDamages;
		invincibility_Timer = invincibility_CD;
	}
}

void Character::heal(float rawHeal)
{
	this->currentHealth = clamp(this->currentHealth + rawHeal, 0, this->maxHealth);
}

void Character::update(float dt)
{
	if (invincibility_Timer > 0)
		invincibility_Timer -= dt;

	applyGravity(dt);

	if (moved)
		manageMovements(dt);

	manageState();
}

void Character::render(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.transform *= getTransform();
	target.draw(*this->spr, states);
}
