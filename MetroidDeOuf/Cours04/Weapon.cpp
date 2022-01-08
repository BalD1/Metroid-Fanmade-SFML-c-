#include "Weapon.hpp"
#include "Game.hpp"

Weapon::Weapon()
{
	this->spr = new sf::RectangleShape();
	this->spr->setSize(sf::Vector2f(20,10));
	this->spr->setOrigin(0, this->spr->getSize().y / 2);
	this->spr->setFillColor(sf::Color::Red);
	this->spr->setPosition(0, 0);

	for (int i = 0; i < poolCount; i++)
	{
		Bullet* b = new Bullet(cx, cy, stride, 5, 7);
		bulletsPool.push_back(b);
	}
}

Weapon::~Weapon()
{
	delete(this->spr);
}

void Weapon::setPosition(float _cx, float _rx, float _cy, float _ry)
{
	cx = _cx;
	rx = _rx;
	cy = _cy;
	ry = _ry;
}

void Weapon::setOffset(sf::Vector2f _offset)
{
	this->offset = _offset;
}

void Weapon::lookAtMouse()
{
	float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));

	this->spr->setRotation(angle);
}

void Weapon::update(float dt)
{
	lookAtMouse();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (CDtimer <= 0)
		{
			fire();
		}
	}
	CDtimer -= dt;

	for (auto b : bulletsPool)
		b->update(dt);
	checkBulletCollision();
}

void Weapon::render(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(*this->spr, states);
	for (auto b : bulletsPool)
		b->render(target);
}

void Weapon::fire()
{
	CDtimer = fireCD;
	for (auto b : bulletsPool)
	{
		if (!b->isActive())
		{
			b->setPosition(this->cx, this->rx, this->cy, this->ry);
			b->setActive(true);
			setBullet(b);
			return;
		}
	}
	Bullet* b = new Bullet(cx, cy, stride, 5, 7);
	bulletsPool.push_back(b);
	setBullet(b);

}

void Weapon::setBullet(Bullet* bullet)
{
	bullet->setPosition(this->cx, this->rx, this->cy, this->ry);

	sf::Vector2f direction = { mousePosition.x - ((cx + rx) * stride), mousePosition.y - ((cy + ry) * stride) };

	bullet->setDirection(sf::Vector2f(NormalizeVector(direction)));
	bullet->setActive(true);
}

void Weapon::checkBulletCollision()
{
	for (auto b : bulletsPool)
	{
		if (b->isActive())
		{
			if (worldRef->colidesWithWall(*b))
				b->setActive(false);
			if (gameRef->checkIfBulletHitsEnemy(b->cx, b->cy, 10))
				b->setActive(false);
		}
	}
}
