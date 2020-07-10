#include "HealthPotion.h"
#include "Creature.h"

HealthPotion::HealthPotion(World* world, const char* name, const char* desc, Entity* parent, int healthToHeal) : Consumable(world, name, desc, parent) {
	this->healthToHeal = healthToHeal;
}

HealthPotion::~HealthPotion() {

}

void HealthPotion::BeConsumed() {
	if (full) {
		cout << parent->name + " Consumed " + name + " and healed " << healthToHeal << " health points\n";
		Creature* user = (Creature*)parent;
		user->health += healthToHeal;
		if (user->health > user->max_health) {
			user->health = user->max_health;
		}
		full = false;
	} else {
		Println(name + " Is Empty!");
	}

}