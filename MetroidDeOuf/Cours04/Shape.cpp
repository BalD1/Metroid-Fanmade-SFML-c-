#include "stdafx.hpp"
#include "Shape.hpp"

sf::CircleShape SetCircle(const int size, const sf::Color color, const sf::Vector2f pos)
{
	sf::CircleShape tmpC(size);
	tmpC.setFillColor(color);
	tmpC.setPosition(pos);

	return tmpC;
}
sf::CircleShape SetCircle(const int size, const sf::Color color, const float posX, const float posY)
{
	sf::CircleShape tmpC(size);
	tmpC.setFillColor(color);
	tmpC.setPosition(posX, posY);

	return tmpC;
}

sf::RectangleShape SetRectangle(const sf::Vector2f size, const sf::Color color, const sf::Vector2f pos)
{
	sf::RectangleShape tmpR(size);
	tmpR.setFillColor(color);
	tmpR.setPosition(pos);

	return tmpR;
}

sf::RectangleShape SetRectangle(const float sizeX, const float sizeY, const sf::Color color, const sf::Vector2f pos)
{
	sf::RectangleShape tmpR(sf::Vector2f(sizeX, sizeY));
	tmpR.setFillColor(color);
	tmpR.setPosition(pos);

	return tmpR;
}

sf::Text SetText(const int size, const std::string txt, const sf::Color color, const sf::Font font)
{
	sf::Text t;
	t.setCharacterSize(size);
	t.setString(txt);
	t.setFillColor(color);
	t.setFont(font);

	return t;
}
