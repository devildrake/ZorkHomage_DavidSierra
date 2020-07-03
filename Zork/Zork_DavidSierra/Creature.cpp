#include "Creature.h"

Creature::Creature(const char* name, const char* desc, Room* initialRoom, int maxHealth, int startingHealth) :Entity(name, desc, (Entity*)initialRoom) {
	this->name = name;
	description = desc;
	this->parent = (Entity*)initialRoom;
	this->parent->entitiesContained.push_back(this);
	max_health = maxHealth;
	health = startingHealth;
}

Creature::Creature(const char* name, const char* desc, Room* initialRoom) :Entity(name, desc, (Entity*)initialRoom) {
	this->name = name;
	description = desc;
	this->parent = (Entity*)initialRoom;
	this->parent->entitiesContained.push_back(this);
	max_health = DEFAULT_MAX_HEALTH;
	health = DEFAULT_MAX_HEALTH;
}

Creature::~Creature() {

}

void Creature::Look()const {
	cout << name << endl;
	cout << description << endl;
}

bool Creature::IsAlive() const {
	return false;
}
