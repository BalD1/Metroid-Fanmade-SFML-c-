#pragma once
#include "Enemy.hpp"

class Player;
class World;

class CharactersManager
{
private:

	const char* charactersFilePath = "Assets/Data/characters.txt";

public:

	Player*							playerRef = nullptr;
	World*							worldRef = nullptr;
	std::vector<Enemy*>				enemies;

	const size_t SIZE_textures = 2;
	sf::Texture*		textures[2];
	const char*	   texturesNames[2] = { "redTexture", "purpleTexture" };

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

