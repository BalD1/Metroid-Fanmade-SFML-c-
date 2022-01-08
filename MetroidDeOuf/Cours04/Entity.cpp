#include "Entity.hpp"

void Entity::init()
{
	this->spr = nullptr;
}

Entity::Entity(float _cx, float _cy, int _stride)
{
	init();
	this->cx = _cx;
	this->cy = _cy;
	this->stride = _stride;
}

Entity::Entity(float _cx, float _cy, int _stride, sf::Texture* _texture)
{
	init();
	this->cx = _cx;
	this->cy = _cy;
	this->stride = _stride;

	this->texture = _texture;
	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);
	syncSprite(1);
}

Entity::~Entity()
{
	if (this == nullptr)
		return;
	if (this->spr)
		delete(spr);
}

void Entity::setTexture(sf::Texture* _texture)
{
	this->texture = _texture;
	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);
	syncSprite(1);
}

void Entity::setTag(const std::string _tag)
{
	this->tag = _tag;
}

const std::string Entity::getTag()
{
	return this->tag;
}

void Entity::syncSprite(float dt)
{
	xx = (cx + rx) * stride;
	yy = (cy + ry) * stride;
	if (this->spr != nullptr)
	this->spr->setPosition(xx, yy);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(*spr);
}

void Entity::update(float dt)
{

}