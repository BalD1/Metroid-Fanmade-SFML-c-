#pragma once
#include "Entity.hpp"

class DeathZone : public Entity
{
private:

public:

	DeathZone(int _cx, int _cy, int _stride);
	DeathZone(int _cx, int _cy, int _stride, sf::Texture& texture);
	~DeathZone();

};

