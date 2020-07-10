#include "Consumable.h"
#include "Creature.h"
Consumable::Consumable(World* world, const char* name, const char* desc, Entity* parent) : Item(world, name, desc, parent, ItemType::CONSUMABLE) {
	itemType = ItemType::CONSUMABLE;
	full = true;
}

void Consumable::BeConsumed() {
	if (full) {
		Println(parent->name + " Consumed " + name);
		full = false;
	} else {
		Println(name + " Is Empty!");
	}
}

void Consumable::Look()const {
	Println(name + " - " + description + (full ? " (Full)": (" (Empty)")));
}