#include "BallItem.hpp"
#include "Player.hpp"

BallItem::BallItem(int _cx, int _cy, int _stride)
	: Item(_cx, _cy, _stride)
{
	this->spr = new sf::Sprite();
	this->texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath))
		printf("Could not load ball item texture from %s", texturePath);

	this->spr->setTexture(*texture);
	syncSprite(1);
	itemType = "Ball";
}

BallItem::~BallItem()
{
}

void BallItem::pickup(Player* playerRef, char inventorySlot)
{
	playerRef->inventory[inventorySlot]++;
	this->canRender = false;
}
