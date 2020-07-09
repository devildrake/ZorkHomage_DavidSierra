#include "NonPlayableCharacter.h"
#include "Room.h"
NonPlayableCharacter::NonPlayableCharacter(const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int a_m, int a_M, int d_m, int d_M, int crit, int miss, bool canDie) : Creature(name, desc, unArmedWeapon, initialRoom, maxHealth, startingHealth, a_m, a_M, d_m, d_M, crit, miss, canDie) {

}
NonPlayableCharacter::~NonPlayableCharacter() {

}

Room* NonPlayableCharacter::GetRoom() const {
	return (Room*)parent;
}


bool NonPlayableCharacter::IsAlive() const {
	return this->health > 0;
}

void NonPlayableCharacter::TakeAction() {

}


void NonPlayableCharacter::Look() const {
	Println(name);
	Println(description);
}