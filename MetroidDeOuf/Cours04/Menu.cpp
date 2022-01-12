#include "Menu.hpp"

Menu::Menu(int _itemNumbers)
{
	if (!baseFont.loadFromFile("Assets/Fonts/basefont.ttf"))
		printf("Couldn't load Assets/Fonts/basefont.ttf");

	itemNumbers = _itemNumbers;
	if (itemNumbers > 0)
	{
		for (int i = 0; i < itemNumbers; i++)
		{
			sf::Text b;
			b.setFillColor(defaultColor);
			menu.push_back(b);
		}
		menu[0].setFillColor(selectedColor);
	}

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

void Menu::setUp(sf::Vector2f screenCenter)
{
}

void Menu::moveUp()
{
	if (itemNumbers > 0)
	{
		audioManagerRef->playSound(select);
		menu[selectedItemIndex].setFillColor(defaultColor);
		if (selectedItemIndex - 1 < 0)
			selectedItemIndex = itemNumbers - 1;
		else
			selectedItemIndex--;

		menu[selectedItemIndex].setFillColor(selectedColor);
	}
}

void Menu::moveDown()
{
	if (itemNumbers > 0)
	{
		audioManagerRef->playSound(select);
		menu[selectedItemIndex].setFillColor(defaultColor);
		if (selectedItemIndex + 1 > itemNumbers - 1)
			selectedItemIndex = 0;
		else
			selectedItemIndex++;

		menu[selectedItemIndex].setFillColor(selectedColor);
	}
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
	menu[buttonIndex].setCharacterSize(textSize);
	menu[buttonIndex].setFont(baseFont);
	menu[buttonIndex].setString(text);
	menu[buttonIndex].setOrigin(menu[buttonIndex].getGlobalBounds().width / 2, menu[buttonIndex].getGlobalBounds().height / 2);
	menu[buttonIndex].setPosition(pos);
}

void Menu::setSelectable(int buttonIndex, std::string text, sf::Vector2f pos)
{
	menu[buttonIndex].setCharacterSize(textSize);
	menu[buttonIndex].setFont(baseFont);
	menu[buttonIndex].setString(text);
	menu[buttonIndex].setOrigin(menu[buttonIndex].getGlobalBounds().width / 2, menu[buttonIndex].getGlobalBounds().height / 2);
	menu[buttonIndex].setPosition(pos);
}

void Menu::setText(const char* text, sf::Vector2f pos)
{
	sf::Text t;
	t.setFont(baseFont);
	t.setString(text);
	t.setCharacterSize(textSize);
	t.setOrigin(t.getGlobalBounds().width / 2, t.getGlobalBounds().height / 2);
	t.setPosition(pos);
	simpleTexts.push_back(t);
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
	for (int i = 0; i < simpleTexts.size(); i++)
		target.draw(simpleTexts[i]);
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

#pragma region MainMenu

MainMenu::MainMenu(sf::Vector2f screenCenter, AudioManager* _audioManagerRef)
	: Menu(4)
{
	audioManagerRef = _audioManagerRef;
	setUp(screenCenter);
}

void MainMenu::setUp(sf::Vector2f screenCenter)
{
	this->setSelectable(0, "Play", sf::Vector2f(screenCenter.x / 2, screenCenter.y / (this->itemNumbers + 1) * 1));
	this->setSelectable(1, "Load Game", sf::Vector2f(screenCenter.x / 2, screenCenter.y / (this->itemNumbers + 1) * 2));
	this->setSelectable(2, "Options", sf::Vector2f(screenCenter.x / 2, screenCenter.y / (this->itemNumbers + 1) * 3));
	this->setSelectable(3, "Exit", sf::Vector2f(screenCenter.x / 2, screenCenter.y / (this->itemNumbers + 1) * 4 - 20));
	this->setPosition(sf::Vector2f(screenCenter.x / 2, screenCenter.y / 2));
}

#pragma endregion

#pragma region PauseMenu

PauseMenu::PauseMenu(sf::Vector2f screenCenter, AudioManager* _audioManagerRef)
	: Menu(3)
{
	audioManagerRef = _audioManagerRef;
	setUp(screenCenter);
}

void PauseMenu::setUp(sf::Vector2f screenCenter)
{
	this->setSelectable(0, "Continue", sf::Vector2f(screenCenter.x, screenCenter.y - 200));
	this->setSelectable(1, "Options", sf::Vector2f(screenCenter.x, screenCenter.y));
	this->setSelectable(2, "Main Menu", sf::Vector2f(screenCenter.x, screenCenter.y + 200));
	this->setPosition(sf::Vector2f(screenCenter.x, screenCenter.y));
}

#pragma endregion

#pragma region OptionsMenu

OptionsMenu::OptionsMenu(sf::Vector2f screenCenter, AudioManager* _audioManagerRef)
	: Menu(3)
{
	audioManagerRef = _audioManagerRef;
	setUp(screenCenter);
}

void OptionsMenu::setUp(sf::Vector2f screenCenter)
{
	std::string vol = "Music Volume : \n" + std::to_string(audioManagerRef->musicVolume);
	this->setSelectable(0, vol, sf::Vector2f(screenCenter.x, screenCenter.y - 50));
	vol = "SFX Volume : \n" + std::to_string(audioManagerRef->sfxVolume);
	this->setSelectable(1, vol, sf::Vector2f(screenCenter.x, screenCenter.y + 50));
	this->setSelectable(2, "Back", sf::Vector2f(screenCenter.x, screenCenter.y + 200));
	this->setPosition(sf::Vector2f(screenCenter.x, screenCenter.y));
}

#pragma endregion

#pragma region GameOverMenu

GameOverMenu::GameOverMenu(sf::Vector2f screenCenter, AudioManager* _audioManagerRef)
	: Menu()
{
	audioManagerRef = _audioManagerRef;
	setUp(screenCenter);
}

void GameOverMenu::setUp(sf::Vector2f screenCenter)
{
	this->setSelectable(0, "Retry", sf::Vector2f(screenCenter.x, screenCenter.y - 100));
	this->setSelectable(1, "Main Menu", sf::Vector2f(screenCenter.x, screenCenter.y + 100));
	this->setPosition(sf::Vector2f(screenCenter.x, screenCenter.y));
}

#pragma endregion

#pragma region WinMenu

WinMenu::WinMenu(sf::Vector2f screenCenter, AudioManager* _audioManagerRef)
	: Menu()
{
	audioManagerRef = _audioManagerRef;
	setUp(screenCenter);
}

void WinMenu::setUp(sf::Vector2f screenCenter)
{
	this->setSelectable(0, "Play Again", sf::Vector2f(screenCenter.x, screenCenter.y - 100));
	this->setSelectable(1, "Main Menu", sf::Vector2f(screenCenter.x, screenCenter.y + 100));
	this->setPosition(sf::Vector2f(screenCenter.x, screenCenter.y));
}

#pragma endregion

TutoMenu::TutoMenu(sf::Vector2f screenCenter, AudioManager* _audioManagerRef)
	: Menu(0)
{
	audioManagerRef = _audioManagerRef;
	this->textSize = 15;
	setUp(screenCenter);
}

void TutoMenu::setUp(sf::Vector2f screenCenter)
{
	this->setText("Congratulations !", sf::Vector2f(screenCenter.x, screenCenter.y - 200));
	this->setText("You found the morphball", sf::Vector2f(screenCenter.x, screenCenter.y - 170));
	this->setText("Press the down and", sf::Vector2f(screenCenter.x, screenCenter.y));
	this->setText("up arrow keys", sf::Vector2f(screenCenter.x, screenCenter.y + 30 ));
	this->setText("On your keyboard or on your", sf::Vector2f(screenCenter.x, screenCenter.y + 60));
	this->setText("controller to morph yourself !", sf::Vector2f(screenCenter.x, screenCenter.y + 90));
	this->setText("Press Enter or start to continue", sf::Vector2f(screenCenter.x, screenCenter.y + 200));
	this->setPosition(sf::Vector2f(screenCenter.x, screenCenter.y));
}
