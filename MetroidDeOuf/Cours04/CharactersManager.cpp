#include "CharactersManager.hpp"

CharactersManager::CharactersManager()
{
}

CharactersManager::~CharactersManager()
{
}

void CharactersManager::addEnemy(Enemy* e)
{
	enemies.push_back(e);
}

std::vector<Enemy*> CharactersManager::getEnemiesList()
{
	return enemies;
}

void CharactersManager::render(sf::RenderTarget& target)
{
	for (auto e : enemies)
		e->render(target);
}

void CharactersManager::update(float dt)
{
	for (auto e : enemies)
		e->update(dt);
}

void CharactersManager::saveCharactersInFile()
{
}

void CharactersManager::loadCharacters(bool eraseCurrentCharacters)
{
}

void CharactersManager::killAll()
{
}
