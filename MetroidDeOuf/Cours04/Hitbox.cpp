#include "stdafx.hpp"
#include "Hitbox.hpp"

Hitbox::Hitbox(sf::Sprite& sprite, float newOffsetX, float newOffsetY, float width, float height) 
	: sprite(sprite), offsetX(newOffsetX), offsetY(newOffsetY)
{
	this->nextPos.left = 0.0f;
	this->nextPos.top = 0.0f;
	this->nextPos.width = width;
	this->nextPos.height = height;
							// size, color, pos
	this->box = SetRectangle(sf::Vector2f(width, height), sf::Color::Transparent,
		sf::Vector2f(this->sprite.getPosition().x + newOffsetX, this->sprite.getPosition().y + newOffsetY));
	this->box.setOutlineThickness(-1.0f);
	this->box.setOutlineColor(sf::Color::Green);
}

Hitbox::~Hitbox()
{
}

const sf::Vector2f& Hitbox::getPosition() const
{
	return this->box.getPosition();
}

const sf::FloatRect Hitbox::getGlobalBounds() const
{
	return this->box.getGlobalBounds();
}

const sf::FloatRect& Hitbox::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPos.left = this->box.getPosition().x + velocity.x;
	this->nextPos.top = this->box.getPosition().y + velocity.y;

	return this->nextPos;
}

void Hitbox::setPosition(const sf::Vector2f& newPosition)
{
	this->box.setPosition(newPosition);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void Hitbox::setPosition(const float newX, const float newY)
{
	this->box.setPosition(newX, newY);
	this->sprite.setPosition(newX - this->offsetX, newY - this->offsetY);
}

void Hitbox::setOffset(const sf::Vector2f _offset)
{
	this->offsetX = _offset.x;
	this->offsetY = _offset.y;
}

void Hitbox::setOffset(const float _x, const float _y)
{
	this->offsetX = _x;
	this->offsetY = _y;
}

const sf::Vector2f Hitbox::getOffset()
{
	return sf::Vector2f(this->offsetX, this->offsetY);
}

bool Hitbox::intersects(const sf::FloatRect& target)
{
	return this->box.getGlobalBounds().intersects(target);
}

void Hitbox::update()
{
	this->box.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void Hitbox::render(sf::RenderTarget& target)
{
	target.draw(this->box);
}


