#pragma once
#include "Enemy.hpp"

class CharactersManager
{
private:

	const char* charactersFilePath = "Assets/Data/characters.txt";

public:

	std::vector<Enemy*>				enemies;

	CharactersManager();
	~CharactersManager();

	void addEnemy(Enemy* e);
	std::vector<Enemy*> getEnemiesList();

	void render(sf::RenderTarget& target);
	void update(float dt);

	void saveCharactersInFile();
	void loadCharacters(bool eraseCurrentCharacters = false);
	void killAll();
};

