#pragma once
#include "stdafx.hpp"

class Menu
{
	// TODO : Refaire les bouttons en sous-classe -
	// class Button {- infos -}
	// class Play : public Button {- comporement -}
	// ...
private:

	sf::Font					baseFont;
	int							selectedItemIndex = 0;
	std::vector<sf::Text>		menu;
	sf::Color					defaultColor = sf::Color::White;
	sf::Color					selectedColor = sf::Color::Red;
	sf::RectangleShape			box;

public:

	int							itemNumbers = 2;

	Menu(int _itemNumbers = 2);
	~Menu();

	void moveUp();
	void moveDown();

	void setPosition(sf::Vector2f pos);
	void setBox(sf::Color c, sf::Vector2f pos, sf::Vector2f size);
	void setSelectable(sf::Text* button, const char* text, sf::Vector2f pos);
	void setSelectable(int buttonIndex, const char* text, sf::Vector2f pos);
	void render(sf::RenderTarget& target);

	std::vector<sf::Text>* getMenu();
	sf::String getSelectedButton();
};


