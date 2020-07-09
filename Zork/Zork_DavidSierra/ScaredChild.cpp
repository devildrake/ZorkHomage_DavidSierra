#include "ScaredChild.h"
#include "Room.h"
ScaredChild::ScaredChild(const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int a_m, int a_M, int d_m, int d_M, int crit, int miss, Entity* doll, Entity* drop, Room* targetRoom, string newDesc, bool canDie) :NonPlayableCharacter(name, desc, unArmedWeapon, initialRoom, maxHealth, startingHealth, a_m, a_M, d_m, d_M, crit, miss, canDie) {
	this->itemToDrop = drop;
	this->doll = doll;
	this->targetRoom = targetRoom;
	this->newDescription = newDesc;
}

ScaredChild::~ScaredChild() {

}

void ScaredChild::TakeAction() {
	if (actionTaken) {
		return;
	}
	bool foundItem = false;
	for (list<Entity*>::const_iterator it = GetRoom()->entitiesContained.begin(); it != GetRoom()->entitiesContained.cend() && !foundItem; ++it) {
		if ((*it) == doll) {
			foundItem = true;
		}
	}
	if (foundItem) {
		Println("The child slowly takes the doll, she whispers in your ear:\n'I saw the monster leaving to the west', she gets up and runs outside, leaving behind a " + itemToDrop->name);
		doll->SetNewParent(this);
		itemToDrop->SetNewParent(GetRoom());
		TeleTransportToRoom(targetRoom);
		description = newDescription;
		actionTaken = true;
	}
}