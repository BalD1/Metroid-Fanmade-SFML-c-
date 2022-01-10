#pragma once
#include "Entity.hpp"

class Checkpoint : public Entity
{
private:

	sf::Texture*				activatedTexture = nullptr;
	sf::Texture*				notActivatedTexture = nullptr;

	bool						activated = false;

public:


	Checkpoint(int _cx, int _cy, int _stride);
	~Checkpoint();

	void update(float dt);
	void render(sf::RenderTarget& target);

	void setActive(bool active);
	bool isActivated() { return activated; };

};

