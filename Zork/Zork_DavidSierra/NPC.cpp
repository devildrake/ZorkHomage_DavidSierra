#include "NPC.h"

NPC::NPC(const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int a_m, int a_M, int d_m, int d_M, int crit, int miss) : Creature(name, desc, unArmedWeapon, initialRoom, maxHealth, startingHealth, a_m, a_M, d_m, d_M, crit, miss) {

}
NPC::~NPC() {

}

Room* NPC::GetRoom() const {
	return nullptr;
}
bool NPC::PlayerInRoom() const {
	return false;
}
bool NPC::IsAlive() const {
	return this->health > 0;
}

void NPC::Look() const {

}