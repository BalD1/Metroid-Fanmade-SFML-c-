#pragma once
#include "stdafx.hpp"

class Particles {
private:

	sf::CircleShape b;
	sf::Color		color;

	std::vector<float>	xx;
	std::vector<float>	yy;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<float> lifeTime;
	std::vector<float> maxLifeTime;

	std::vector<bool>	alive;

public:


	Particles(sf::Color _color, float size);

	void create(float xx, float yy, float dx, float dy, float lifeTime, int amount);
	void update(float dt);

	void render(sf::RenderTarget& target);
};

