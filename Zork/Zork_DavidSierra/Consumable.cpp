#include "Consumable.h"

Consumable::Consumable(const char* name, const char* desc, Entity* parent) : Item(name, desc, parent, ItemType::CONSUMABLE) {

}

void Consumable::Consume() {
	Println("Consuming " + name);
}