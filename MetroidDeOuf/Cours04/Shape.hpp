#pragma once

sf::CircleShape SetCircle(const int size, const sf::Color color, const sf::Vector2f pos);
sf::CircleShape SetCircle(const int size, const sf::Color color, const float posX, const float posY);

sf::RectangleShape SetRectangle(const sf::Vector2f size, const sf::Color color, const sf::Vector2f pos);
sf::RectangleShape SetRectangle(const float sizeX, const float sizeY, const sf::Color color, const sf::Vector2f pos);

sf::Text SetText(const int size, const std::string txt, const sf::Color color, const sf::Font font);