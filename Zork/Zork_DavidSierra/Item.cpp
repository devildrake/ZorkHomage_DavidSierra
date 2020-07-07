#include "Item.h"

Item::Item(const char*name, const char*desc, Entity*parent, ItemType anItemType) :Entity(name, desc, parent) {
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