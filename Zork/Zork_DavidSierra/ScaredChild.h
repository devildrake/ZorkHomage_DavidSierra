#pragma once
#include "NonPlayableCharacter.h"

//Specific class for a NonPlayableCharacter with a specific interaction
class ScaredChild : public NonPlayableCharacter {
public:
	ScaredChild(World* world, const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int a_m, int a_M, int d_m, int d_M, int crit, int miss, Entity* doll, Entity* drop, Room* targetRoom, string newDesc, bool canDie = false);
	~ScaredChild();
	void TakeAction();
	Entity* doll;
	Entity*itemToDrop;
	Room* targetRoom;
	string newDescription;
};