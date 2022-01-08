#pragma once
#include "Shape.hpp"

class Hitbox
{
private:

	sf::Sprite& sprite;
	sf::RectangleShape box;
	sf::FloatRect nextPos;
	sf::Vector2f position;
	float offsetX = 0;
	float offsetY = 0;

public:

	Hitbox(sf::Sprite& sprite, float newOffsetX, float newOffsetY, float width, float height);
	~Hitbox();

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	void setPosition(const sf::Vector2f& newPosition);
	void setPosition(const float newX, const float newY);

	void setOffset(const sf::Vector2f _offset);
	void setOffset(const float _x, const float _y);
	const sf::Vector2f getOffset();

	bool intersects(const sf::FloatRect& target);
	
	void update();
	void render(sf::RenderTarget& target);

};

