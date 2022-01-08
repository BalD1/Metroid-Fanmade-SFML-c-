#pragma once
#include "Entity.hpp"

class DeathZone : public Entity
{
private:

public:

	DeathZone(float _cx, float _cy, int _stride);
	DeathZone(float _cx, float _cy, int _stride, sf::Texture& texture);
	~DeathZone();

};

