#pragma once
#include "Creature.h"

class Item;
class Room;

//Entity type fro creatures that don't necesarily attack the player, these may implement an Interact or Talk method
class NonPlayableCharacter : public Creature {
public:
	bool actionTaken;
	NonPlayableCharacter(World* world, const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int a_m, int a_M, int d_m, int d_M, int crit, int miss, bool canDie = false);
	~NonPlayableCharacter();
	Room* GetRoom() const;
	bool IsAlive() const;
	void Look() const;
	void TakeAction();
};