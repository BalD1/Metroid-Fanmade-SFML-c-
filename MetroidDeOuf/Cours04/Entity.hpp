#pragma once
#include "stdafx.hpp"

class Entity
{
private: 
	void init();

public:

#pragma region Variables

	sf::Sprite*			spr = nullptr;
	sf::Texture*		texture = nullptr;

	std::string			tag = "";

#pragma region Grid
						// grid coordinates
	int					cx = 0;
	int					cy = 0;
						// ratios of player position inside cells
	float				rx = 0.0f;
	float				ry = 0.0f;

						// coordinates from (cx+rx) : (cy+ry)
	float				xx = 0.0f;
	float				yy = 0.0f;

						// movements
	float				dx = 0.0f;
	float				dy = 0.0f;

	float				frict_x = 0.67f;
	float				frict_y = 0.65f;

	int					stride = 32;

#pragma endregion


#pragma endregion

#pragma region Funcs

	Entity(float _cx, float _cy, int _stride);
	Entity(float _cx, float _cy, int _stride, sf::Texture* _texture);

	~Entity();

	void setTexture(sf::Texture* _texture);
	void setTag(const std::string _tag);
	const std::string getTag();

	void syncSprite(float dt);
	void render(sf::RenderTarget& target);

	void update(float dt);


#pragma endregion
};