#include "DeathZone.hpp"

DeathZone::DeathZone(float _cx, float _cy, int _stride)
	: Entity(_cx, _cy, _stride)
{
	this->texture = new sf::Texture();
	if (!texture->loadFromFile("Assets/Graphs/deathzone.png"))
		printf("deathzone texture could not be loaded in Assets/Graphs/deathzone.png");

	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);
	syncSprite(1);
}

DeathZone::DeathZone(float _cx, float _cy, int _stride, sf::Texture& texture)
	: Entity(_cx, _cy, _stride)
{
	this->spr = new sf::Sprite();
	this->spr->setTexture(texture);
	syncSprite(1);
}

DeathZone::~DeathZone()
{
}
