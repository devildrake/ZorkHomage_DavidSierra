#pragma once
#include "Item.h"

class Consumable :public Item {
	Consumable(const char* name, const char* desc, Entity* parent);
	virtual void Consume();
};