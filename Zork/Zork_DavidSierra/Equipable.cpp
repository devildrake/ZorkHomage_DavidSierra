#include "Equipable.h"

Equipable::Equipable(World* world, const char* name, const char* desc, Entity* parent, ItemType type, std::pair<int, int>bonusAttack, std::pair<int, int>bonusDefense) : Item(world, name, desc, parent, type) {
	attack_bonus = bonusAttack;
	defense_bonus = bonusDefense;
}

void Equipable::Look()const {
	Println(name + " - " + description + " (" + (itemType == ItemType::ARMOUR ? "Armour" : "Weapon") + ")");
}

void Equipable::Inspect()const {
	Look();
	cout << " - Bonus attack: " << attack_bonus.first << " - " << attack_bonus.second << endl
		<< " - BonusDefense: " << defense_bonus.first << " - " << defense_bonus.second << endl;
}