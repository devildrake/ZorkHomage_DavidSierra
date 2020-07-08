#pragma once
#include "Creature.h"

class Item;
class Room;

class NPC : Creature {
	NPC(const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int a_m, int a_M, int d_m, int d_M, int c_m, int c_M);
	~NPC();

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;
	void Look() const;
};