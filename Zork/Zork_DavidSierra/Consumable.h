#pragma once
#include "Item.h"

//Entity type that can be "consumed"
class Consumable :public Item {
public:
	bool full;
	Consumable(World* world, const char* name, const char* desc, Entity* parent);
	virtual void BeConsumed();
	void Look()const;
};