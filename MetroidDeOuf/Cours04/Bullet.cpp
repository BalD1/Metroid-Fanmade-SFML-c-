#include "Bullet.hpp"

Bullet::Bullet(float _cx, float _cy, int stride, float _size, float _speed, sf::Vector2f _direction)
	: Entity(_cx, _cy, stride)
{
	this->spr = new sf::CircleShape();
	this->spr->setRadius(_size);
	this->spr->setFillColor(sf::Color(255, 127, 0));
	this->speed = _speed;
	if (_direction != sf::Vector2f(0, 0))
		direction = _direction;

	soundOrigin = new sf::Sound();
	soundOrigin->setRelativeToListener(true);
	wallHitSound = new sf::SoundBuffer();
	if (!wallHitSound->loadFromFile("Assets/Sounds/wallhit.wav"))
		printf("Could not load wall hit sound from Assets/Sounds/wallhit.wav");

	hitParticles = new Particles(sf::Color::Yellow, 1);
}

Bullet::~Bullet()
{
	delete(wallHitSound);
	delete(soundOrigin);
	delete(hitParticles);
	delete(this->spr);
}

void Bullet::setPosition(float _cx, float _rx, float _cy, float _ry)
{
	cx = _cx;
	rx = _rx;
	cy = _cy;
	ry = _ry;

	this->syncSprite(1);
}

void Bullet::setDirection(sf::Vector2f dir)
{
	this->dx = dir.x * speed;
	this->dy = dir.y * speed;
}

void Bullet::manageMovements(float dt)
{
	// x
	rx += dx * dt;

	while (rx > 1) { rx--; cx++; }
	while (rx < 0) { rx++; cx--; }

	// y
	ry += dy * dt;

	while (ry > 1) { ry--; cy++; }
	while (ry < 0) { ry++; cy--; }

	this->syncSprite(1);
}

void Bullet::syncSprite(float dt)
{
	xx = (cx + rx) * stride;
	yy = (cy + ry) * stride;
	soundOrigin->setPosition(xx, yy, 0);
	if (this->spr != nullptr)
		this->spr->setPosition(xx, yy);
}

void Bullet::createParticles()
{
	hitParticles->create(xx, yy, 300, 300, 0.3f, 2);
}

void Bullet::playWallHitSound()
{
	audioManagerRef->playSound(wallHitSound, soundOrigin);
}

void Bullet::setActive(bool _active)
{
	this->active = _active;
}


void Bullet::update(float dt)
{
	if (active)
		manageMovements(dt);
	hitParticles->update(dt);
}

void Bullet::render(sf::RenderTarget& target)
{
	if (active)
		target.draw(*this->spr);
	hitParticles->render(target);
}
