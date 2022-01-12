#pragma once
#include "Entity.hpp"

class Player;

class Item : public Entity
{
protected:

	const char*				itemType = "";

public:

	Item(int _cx, int _cy, int _stride);
	~Item();

	bool compareType(const char* _type);

	virtual void pickup(Player* playerRef, char inventorySlot);
};

