#pragma once
#include "Item.hpp"

class BallItem : public Item
{
private:

	const char*				texturePath = "Assets/Graphs/ballitem.png";

public:

	BallItem(int _cx, int _cy, int _stride);
	~BallItem();

	void pickup(Player* playerRef, char inventorySlot);
};

