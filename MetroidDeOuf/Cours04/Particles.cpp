#include "Particles.hpp"

Particles::Particles(sf::Color _color, float size)
{
	b = sf::CircleShape(size);
	b.setFillColor(color);
	color = _color;
	b.setOrigin(sf::Vector2f(size, size));
}

void Particles::create(float _xx, float _yy, float _dx, float _dy, float _lifeTime, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		bool createNew = true;
		for (int j = 0; j < xx.size(); j++)
		{
			if (!alive[j])
			{
				xx[j] = _xx;
				yy[j] = _yy;
				dx[j] = _dx;
				dy[j] = _dy;
				   
				dx[j] = static_cast<float>(rand() % ((int)_dx * 2 + 1) + (-_dx));
				dy[j] = static_cast<float>(rand() % ((int)_dy * 2 + 1) + (-_dy));

				lifeTime[j] = _lifeTime;
				maxLifeTime[j] = _lifeTime;
				alive[j] = true;
				createNew = false;	
				break;
			}
		}
		if (createNew)
		{
			xx.push_back(_xx);
			yy.push_back(_yy);
			_dx = static_cast<float>(rand() % ((int)_dx * 2 + 1) + (-_dx));
			_dy = static_cast<float>(rand() % ((int)_dy * 2 + 1) + (-_dy));
			dx.push_back(_dx);
			dy.push_back(_dy);
			lifeTime.push_back(_lifeTime);
			maxLifeTime.push_back(_lifeTime);
			alive.push_back(true);
		}
	}
}

void Particles::update(float dt) 
{
	for (int i = 0; i < xx.size(); ++i) 
	{
		lifeTime[i] -= dt;
		if (lifeTime[i] <= 0)
			alive[i] = false;

		if (alive[i]) 
		{
			b.setFillColor(sf::Color(color.r, color.g, color.b, 255 * (lifeTime[i] / maxLifeTime[i])));
			xx[i] += dx[i] * dt;
			yy[i] += dy[i] * dt;
		}
	}
}

void Particles::render(sf::RenderTarget& target) 
{
	int idx = 0;
	const int sz = xx.size();
	while (idx < sz)
	{
		if (alive[idx])
		{
			b.setPosition(xx[idx], yy[idx]);
			target.draw(b);
		}
		idx++;
	}
}