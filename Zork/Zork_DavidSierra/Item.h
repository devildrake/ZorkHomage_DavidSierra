#pragma once
#include "Entity.h"

enum ItemType {
	WEAPON,
	ARMOUR,
	CONSUMABLE,
	MISC
};

class Item :public Entity {
public:
	ItemType itemType;
	Item(const char* name, const char* desc, Entity* parent, ItemType itemType = ItemType::MISC);
	~Item();
	void Look() const;
	virtual void Inspect()const;

};