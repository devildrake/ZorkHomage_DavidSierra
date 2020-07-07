#pragma once
#include "Item.h"
class Equipable :public Item {
public:
	Equipable(const char* name, const char* desc, Entity* parent, ItemType type, std::pair<int, int>bonusAttack, std::pair<int, int>bonusDefense);
	pair<int, int>attack_bonus;
	pair<int, int>defense_bonus;
	virtual void Inspect()const;
	void Look()const;
};