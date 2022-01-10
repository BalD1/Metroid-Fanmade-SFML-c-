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

void World::placeCheckPoint(int _cx, int _cy)
{
	for (size_t i = 0; i < checkpoints.size(); ++i)
	{
		if (checkpoints[i]->cx == _cx && checkpoints[i]->cy == _cy)
		{
			delete(checkpoints[i]);
			checkpoints.erase(checkpoints.begin() + i);
			return;
		}
	}
	Checkpoint* cp = new Checkpoint(_cx, _cy, stride);
	checkpoints.push_back(cp);
}

void World::eraseMap()
{
	for (Entity* e : entities)
		delete(e);
	entities.clear();
	for (DeathZone* dz : deathZones)
		delete(dz);
	deathZones.clear();
	delete(winzone);
}

void World::placeWinZone(int _cx, int _cy)
{
	delete(winzone);
	winzone = new WinZone(_cx, _cy, stride);
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
	for (auto dz : deathZones)
		dz->render(target);
	for (auto cp : checkpoints)
		cp->render(target);
	if (winzone != nullptr)
	winzone->render(target);
}

void World::saveMapInFile()
{
	FILE* f = nullptr;
	fopen_s(&f, mapFilePath, "wb");
	if (f)
	{
		std::string entityData = "";

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
		for (Checkpoint* cp : checkpoints)
		{
			entityData = "";
			if (cp->isActivated())
				entityData += "checkpointA ";
			else
				entityData += "checkpoint ";

			entityData += std::to_string(cp->cx) + " " + std::to_string(cp->cy) + "\n";
			fprintf(f, entityData.c_str());
		}
		if (winzone != nullptr)
		{
			entityData = "winzone ";
			entityData += std::to_string(winzone->cx) + " " + std::to_string(winzone->cy) + "\n";
			fprintf(f, entityData.c_str());
		}
		fflush(f);
		fclose(f);
	}
}

void World::loadMap(bool eraseCurrentMap)
{
	worldInitialized = false;
	if (eraseCurrentMap)
		eraseMap();

	FILE* f = nullptr;
	fopen_s(&f, mapFilePath, "rb");
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
			else if (strcmp(line, "checkpoint") == 0)
			{
				Checkpoint* cp = new Checkpoint(_cx, _cy, stride);
				checkpoints.push_back(cp);
			}
			else if (strcmp(line, "checkpointA") == 0)
			{
				Checkpoint* cp = new Checkpoint(_cx, _cy, stride);
				cp->setActive(true);
				checkpoints.push_back(cp);
			}
			else if (strcmp(line, "winzone") == 0)
			{
				winzone = new WinZone(_cx, _cy, stride);
			}

			if (feof(f))
				break;
		}
		fclose(f);
	}

	worldInitialized = true;
}

