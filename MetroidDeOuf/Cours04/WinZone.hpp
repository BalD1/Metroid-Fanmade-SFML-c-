#pragma once
#include "Entity.hpp"

class WinZone : public Entity
{
private:

	sf::Texture* texture = nullptr;

public:

	WinZone(int _cx, int _cy, int _stride);
	~WinZone();

	void render(sf::RenderTarget& target);

};

