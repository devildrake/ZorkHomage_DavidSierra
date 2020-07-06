#include "Item.h"

Item::Item(const char*name, const char*desc, Entity*parent) :Entity(name, desc, parent) {
	type = EntityType::ITEM;
}

Item::~Item() {

}

void Item::Look() const {
	cout << name << " - " << description << endl;
}