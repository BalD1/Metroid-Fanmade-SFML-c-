#pragma once
#include "Enemy.hpp"

class Player;
class World;

class CharactersManager
{
private:

	const char* charactersFilePath = "Assets/Data/characters.txt";
	const char* charactersSavedFilePath = "Assets/Data/Save/characters.txt";

	void save(const char* filePath);
	void load(const char* filePath);

public:

	Player*							playerRef = nullptr;
	World*							worldRef = nullptr;
	AudioManager*					audioManager = nullptr;
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
	void saveCharactersInSave();
	void loadCharactersFromSave();

	void killAll();
};

