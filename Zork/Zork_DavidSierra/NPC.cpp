#include "NPC.h"

NPC::NPC(const char* name, const char* desc, Room* initialRoom, int maxHealth, int startingHealth) : Creature(name, desc, initialRoom, maxHealth, startingHealth) {

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