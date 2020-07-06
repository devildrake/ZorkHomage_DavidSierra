#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent) {
	this->name = name;
	this->description = description;
	this->parent = parent;

	if (parent != NULL) {
		parent->entitiesContained.push_back(this);
	}
}


Entity::~Entity() {

}

//Print name and description
void Entity::Look()const {
	Println(name + " - " + description);
}

void Entity::SetNewParent(Entity* newParent) {

	if (parent != nullptr) {
		parent->entitiesContained.remove((Entity*)this);
	}
	parent = newParent;

	if (parent != nullptr) {
		parent->entitiesContained.push_back((Entity*)this);
	}

}



Entity* Entity::GetChildNamed(const char* targetName) const {
	Entity* e = nullptr;
	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend() && e == nullptr; ++it) {
		e = *it;
		if (!CompareStrings(targetName, e->name)) {
			e = nullptr;
		}
	}
	return e;
}
