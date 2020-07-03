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
	cout << name << endl;
	cout << description << endl;
}