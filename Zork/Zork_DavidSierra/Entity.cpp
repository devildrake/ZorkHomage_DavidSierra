#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent) {
	this->name = name;
	this->description = description;
	this->parent = parent;
	if (parent != nullptr) {
		parent->entitiesContained.push_back(this);
	}
}

void Entity::TakeAction() {

}

Entity::~Entity() {

}

//Print name and description, some exceptions are implemented (Room)
void Entity::Look()const {
	Println(name + " - " + description);
}

vector<Entity*> Entity::GetChildrenOfType(EntityType type)const {
	vector<Entity*>res;

	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it) {
		Entity* e = *it;
		if (e->entityType == type) {
			res.push_back(e);
		}
	}
	return res;
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
