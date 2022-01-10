#include "WinZone.hpp"

WinZone::WinZone(int _cx, int _cy, int _stride)
	: Entity(_cx, _cy, _stride)
{
	this->texture = new sf::Texture();
	if (!texture->loadFromFile("Assets/Graphs/winzone.png"))
		printf("Could not load winzone texture from Assets/Graphs/winzone.png");

	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);
	this->syncSprite(1);
}

WinZone::~WinZone()
{
	delete(texture);
}

void WinZone::render(sf::RenderTarget& target)
{
	target.draw(*spr);
}
