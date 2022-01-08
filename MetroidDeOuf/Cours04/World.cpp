#include "World.hpp"
#include "Enemy.hpp"

World::World(int _stride)
{
	this->stride = _stride;

	this->wallTexture = new sf::Texture();
	if (!wallTexture->loadFromFile("Assets/Graphs/mur.png"))
		printf("Mur texture could not be loaded in Assets/Graphs/mur.png");
	this->deathzoneTexture = new sf::Texture();
	if (!deathzoneTexture->loadFromFile("Assets/Graphs/deathzone.png"))
		printf("Mur texture could not be loaded in Assets/Graphs/deathzone.png");
}

World::~World()
{
}

bool World::colidesWithWall(Entity target)
{
	for (auto w : entities)
	{
		if (target.cx == w->cx && target.cy == w->cy)
			return true;
	}
	return false;
}

void World::placeDeathZone(int _cx, int _cy)
{
	if (_cx > mapLength || _cy > mapLength)
		return;
	for (size_t i = 0; i < deathZones.size(); ++i)
	{
		if (deathZones[i]->cx == _cx && deathZones[i]->cy == _cy)
		{
			delete(deathZones[i]);
			deathZones.erase(deathZones.begin() + i);
			return;
		}
	}
	DeathZone* dz = new DeathZone(_cx, _cy, stride, *deathzoneTexture);
	deathZones.push_back(dz);
}

void World::placeWall(int _cx, int _cy)
{
	if (_cx > mapLength || _cy > mapLength)
		return;
	for (size_t i = 0; i < entities.size(); ++i)
	{
		if (entities[i]->cx == _cx && entities[i]->cy == _cy)
		{
			delete(entities[i]);
			entities.erase(entities.begin() + i);
			return;
		}
	}
	Entity* wall = new Entity(_cx, _cy, stride, wallTexture);
	entities.push_back(wall);
}

void World::eraseMap()
{
	for (Entity* e : entities)
		delete(e);
	entities.clear();
	for (DeathZone* dz : deathZones)
		delete(dz);
	deathZones.clear();
}

void World::deleteEntities()
{
	for (auto e : entitiesToDelete)
		delete(e);
}

void World::render(sf::RenderTarget& target)
{
	for (auto e : entities)
		e->render(target);
	if (renderDeathZones)
	{
		for (auto dz : deathZones)
			dz->render(target);
	}
}

void World::saveMapInFile(const char* filePath)
{
	FILE* f = nullptr;
	fopen_s(&f, filePath, "wb");
	if (f)
	{
		std::string entityData = "";

		if (entities.size() > 0)
		{
			for (Entity* e : entities)
			{
				entityData = "";
				if (e->texture == wallTexture)
					entityData += "wall ";

				entityData += std::to_string(e->cx) + " " + std::to_string(e->cy) + "\n";
				fprintf(f, entityData.c_str());
			}
			for (DeathZone* dz : deathZones)
			{
				entityData = "";
				entityData += "deathzone ";

				entityData += std::to_string(dz->cx) + " " + std::to_string(dz->cy) + "\n";
				fprintf(f, entityData.c_str());
			}
		}
		fflush(f);
		fclose(f);
	}
}

void World::loadMap(const char* filePath, bool eraseCurrentMap)
{
	worldInitialized = false;
	if (eraseCurrentMap)
		eraseMap();

	FILE* f = nullptr;
	fopen_s(&f, filePath, "rb");
	if (f)
	{
		char line[256] = {};
		while (true)
		{
			int64_t _cx = 0;
			int64_t _cy = 0;
			fscanf_s(f, "%s %lld %lld\n", line, 256, &_cx, &_cy);
			if (strcmp(line, "wall") == 0)
			{
				Entity* w = new Entity(_cx, _cy, stride, wallTexture);
				entities.push_back(w);
			}
			else if (strcmp(line, "deathzone") == 0)
			{
				DeathZone* dz = new DeathZone(_cx, _cy, stride, *deathzoneTexture);
				deathZones.push_back(dz);
			}

			if (feof(f))
				break;
		}
		fclose(f);
	}

	worldInitialized = true;
}

