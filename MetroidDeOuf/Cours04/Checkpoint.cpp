#include "Checkpoint.hpp"

Checkpoint::Checkpoint(int _cx, int _cy, int _stride)
	: Entity(_cx, _cy, _stride)
{
	activatedTexture = new sf::Texture();
	if (!activatedTexture->loadFromFile("Assets/Graphs/checkpointactv.png"))
		printf("Could not load activated checkpoint texture from Assets/Graphs/checkpointactv.png");
	notActivatedTexture = new sf::Texture();
	if (!notActivatedTexture->loadFromFile("Assets/Graphs/checkpointnotactv.png"))
		printf("Could not load not activated checkpoint texture from Assets/Graphs/checkpointnotactv.png");

	this->spr = new sf::Sprite();
	this->spr->setTexture(*notActivatedTexture);
	syncSprite(1);
}

Checkpoint::~Checkpoint()
{
	delete(activatedTexture);
	delete(notActivatedTexture);
}

void Checkpoint::update(float dt)
{
}

void Checkpoint::render(sf::RenderTarget& target)
{
	target.draw(*this->spr);
}

void Checkpoint::setActive(bool active)
{
	activated = active;
	this->spr->setTexture(*activatedTexture);
}
