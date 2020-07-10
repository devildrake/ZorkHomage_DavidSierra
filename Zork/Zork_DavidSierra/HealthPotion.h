#pragma once
#include "Consumable.h"

//Potion that upon use, heals the player
class HealthPotion :public Consumable {
	int healthToHeal;
public:
	HealthPotion(World* world, const char* name, const char* desc, Entity* parent, int healthToHeal);
	~HealthPotion();
	void BeConsumed();
};