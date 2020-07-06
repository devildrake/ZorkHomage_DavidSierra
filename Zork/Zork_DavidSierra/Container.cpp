#include "Container.h"
#include "Item.h"

Container::Container(const char*name, const char*desc, Entity*parent, Entity* keyToUnlock) :Entity(name, desc, parent) {
	type = EntityType::CONTAINER;

	if (keyToUnlock != nullptr) {
		this->keyToUnlock = keyToUnlock;
		isLocked = true;
	}

}

Container::~Container() {

}

void Container::Look() const {

	Println(name + " - " + description + " (" + (isLocked ? "Locked" : "Unlocked") + ")");

	if (entitiesContained.size() > 0 && !isLocked) {
		Println("There're some things inside:");
		for (std::list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it) {
			cout << " - " + (*it)->name << endl;
		}
	} else {
		Println("There may be some things inside");
	}

}