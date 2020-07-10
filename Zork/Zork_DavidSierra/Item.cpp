#include "Item.h"

Item::Item(World* world, const char*name, const char*desc, Entity*parent, ItemType anItemType) :Entity(world, name, desc, parent) {
	entityType = EntityType::ITEM;
	itemType = anItemType;
}

Item::~Item() {

}

void Item::Look() const {
	cout << name << " - " << description << endl;
}

void Item::Inspect()const {

}