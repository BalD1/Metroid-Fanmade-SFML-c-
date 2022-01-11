#pragma once
#include "stdafx.hpp"
#include "AudioManager.hpp"

class Menu
{
	// TODO : Refaire les bouttons en sous-classe -
	// class Button {- infos -}
	// class Play : public Button {- comporement -}
	// ...
private:

	sf::Font					baseFont;
	float						textSize = 20;
	int							selectedItemIndex = 0;
	std::vector<sf::Text>		menu;
	sf::Color					defaultColor = sf::Color::White;
	sf::Color					selectedColor = sf::Color::Red;
	sf::Sprite*					box;
	sf::Texture*				boxTexture = nullptr;

	sf::SoundBuffer*			click = nullptr;
	sf::SoundBuffer*			select = nullptr;

public:

	AudioManager*				audioManagerRef = nullptr;
	int							itemNumbers = 2;

	Menu(int _itemNumbers = 2);
	~Menu();

	void moveUp();
	void moveDown();

	void setPosition(sf::Vector2f pos);
	void setSelectable(sf::Text* button, const char* text, sf::Vector2f pos);
	void setSelectable(int buttonIndex, const char* text, sf::Vector2f pos);
	void setSelectable(int buttonIndex, std::string text, sf::Vector2f pos);

	bool manageMouse(sf::Vector2i mousePosition);

	void render(sf::RenderTarget& target);

	std::vector<sf::Text>* getMenu();
	sf::String getSelectedButton();
};


