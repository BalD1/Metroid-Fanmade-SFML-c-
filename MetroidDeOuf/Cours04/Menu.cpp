#include "Menu.hpp"

Menu::Menu(int _itemNumbers)
{
	if (!baseFont.loadFromFile("Assets/Fonts/basefont.ttf"))
		printf("Couldn't load Assets/Fonts/basefont.ttf");

	itemNumbers = _itemNumbers;
	for (int i = 0; i < itemNumbers; i++)
	{
		sf::Text b;
		b.setFillColor(defaultColor);
		menu.push_back(b);
	}
	menu[0].setFillColor(selectedColor);

	click = new sf::SoundBuffer();
	if (!click->loadFromFile("Assets/Sounds/click.wav"))
		printf("Could not load click sound from Assets/Sounds/click.wav");
	select = new sf::SoundBuffer();
	if (!select->loadFromFile("Assets/Sounds/select.wav"))
		printf("Could not load select sound from Assets/Sounds/select.wav");

	box = new sf::Sprite();
	boxTexture = new sf::Texture();
	if (!boxTexture->loadFromFile("Assets/Graphs/menupanel.png"))
		printf("Could not load menu box texture from Assets/Graphs/menupanel.png");
	box->setOrigin(boxTexture->getSize().x / 2, boxTexture->getSize().y / 2);
	box->setTexture(*boxTexture);
}

Menu::~Menu()
{
	delete(click);
	delete(select);
	delete(box);
	delete(boxTexture);
}

void Menu::moveUp()
{
	audioManagerRef->playSound(select);
	menu[selectedItemIndex].setFillColor(defaultColor);
	if (selectedItemIndex - 1 < 0)
		selectedItemIndex = itemNumbers - 1;
	else
		selectedItemIndex--;

	menu[selectedItemIndex].setFillColor(selectedColor);
}

void Menu::moveDown()
{
	audioManagerRef->playSound(select);
	menu[selectedItemIndex].setFillColor(defaultColor);
	if (selectedItemIndex + 1 > itemNumbers - 1)
		selectedItemIndex = 0;
	else
		selectedItemIndex++;

	menu[selectedItemIndex].setFillColor(selectedColor);
}

void Menu::setPosition(sf::Vector2f pos)
{
	box->setPosition(pos);
}

void Menu::setSelectable(sf::Text* button, const char* text, sf::Vector2f pos)
{
	button->setFont(baseFont);
	button->setString(text);
	button->setOrigin(button->getGlobalBounds().width / 2, button->getGlobalBounds().height / 2);
	button->setPosition(pos);
}

void Menu::setSelectable(int buttonIndex, const char* text, sf::Vector2f pos)
{
	menu[buttonIndex].setFont(baseFont);
	menu[buttonIndex].setString(text);
	menu[buttonIndex].setOrigin(menu[buttonIndex].getGlobalBounds().width / 2, menu[buttonIndex].getGlobalBounds().height / 2);
	menu[buttonIndex].setPosition(pos);
}

bool Menu::manageMouse(sf::Vector2i mousePosition)
{
	for (int i = 0; i < itemNumbers; i++)
	{
		if (menu[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			if (selectedItemIndex != i)
			{
				audioManagerRef->playSound(select);
				menu[selectedItemIndex].setFillColor(defaultColor);
				selectedItemIndex = i;
				menu[selectedItemIndex].setFillColor(selectedColor);
			}
				return true;
		}
	}
	return false;
}

void Menu::render(sf::RenderTarget& target)
{
	target.draw(*box);
	for (int i = 0; i < itemNumbers; i++)
		target.draw(menu[i]);
}

std::vector<sf::Text>* Menu::getMenu()
{
	return &menu;
}

sf::String Menu::getSelectedButton()
{
	audioManagerRef->playSound(click);
	return menu[selectedItemIndex].getString();
}
