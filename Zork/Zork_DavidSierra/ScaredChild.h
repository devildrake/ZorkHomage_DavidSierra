#pragma once
#include "NonPlayableCharacter.h"

class ScaredChild : public NonPlayableCharacter {
public:
	ScaredChild(const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int a_m, int a_M, int d_m, int d_M, int crit, int miss, Entity* doll, Entity* drop, Room* targetRoom, string newDesc);
	~ScaredChild();
	void TakeAction();
	Entity* doll;
	Entity*itemToDrop;
	Room* targetRoom;
	string newDescription;
};