#include "CharactersManager.hpp"

CharactersManager::CharactersManager()
{
	textures[0] = new sf::Texture();
	if (!textures[0]->loadFromFile("Assets/Graphs/red.png"))
		printf("red texture could not be loaded in Assets/Graphs/red.png");
	textures[1] = new sf::Texture();
	if (!textures[1]->loadFromFile("Assets/Graphs/purple.png"))
		printf("purple texture could not be loaded in Assets/Graphs/purple.png");
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
	FILE* f = nullptr;
	fopen_s(&f, charactersFilePath, "wb");
	if (f)
	{
		std::string entityData = "";

		if (enemies.size() > 0)
		{
			for (Enemy* e : enemies)
			{
				entityData = e->name + " ";

				for (int i = 0; i < SIZE_textures; i++)
				{
					if (e->spr->getTexture() == textures[i])
						entityData += std::to_string(i) + " ";
				}

				entityData += std::to_string((int)e->currentHealth) + " " + std::to_string((int)e->maxHealth) + " ";

				entityData += std::to_string(e->cx) + " " + std::to_string(e->cy) + "\n";
				fprintf(f, entityData.c_str());
			}
		}
		fflush(f);
		fclose(f);
	}
}

void CharactersManager::loadCharacters(bool eraseCurrentCharacters)
{
	FILE* f = nullptr;
	fopen_s(&f, charactersFilePath, "rb");
	if (f)
	{
		char line[256] = {};
		while (true)
		{
			int64_t _texture = 0;
			int64_t _currPv = 0;
			int64_t _maxPv = 0;
			int64_t _cx = 0;
			int64_t _cy = 0;
			//nom texture currPv maxPv posX posY
			fscanf_s(f, "%s %lld %lld %lld %lld %lld\n", line, 256, &_texture, &_currPv, &_maxPv, &_cx, &_cy);
			std::string name;
			name.assign(line);

			Enemy* e = new Enemy(name, (int)_cx, (int)_cy, 32, *textures[_texture]);
			e->maxHealth = _maxPv;
			e->currentHealth = _currPv;
			e->setWorld(worldRef);
			e->setPlayer(playerRef);

			enemies.push_back(e);

			if (feof(f))
				break;
		}
		fclose(f);
	}
}

void CharactersManager::killAll()
{
}
