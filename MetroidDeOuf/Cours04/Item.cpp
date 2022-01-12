#include "Item.hpp"

Item::Item(int _cx, int _cy, int _stride)
	: Entity(_cx, _cy, _stride)
{
}

Item::~Item()
{
}

void Item::pickup(Player* playerRef, char inventorySlot)
{
}

bool Item::compareType(const char* _type)
{
	if (strcmp(_type, this->itemType) == 0)
		return true;
	return false;
}
