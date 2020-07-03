#pragma once
#include "Creature.h"

class Item;
class Room;

class NPC : Creature {
	NPC(const char* name, const char* desc, Room* initialRoom, int maxHealth, int startingHealth);
	~NPC();

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;
	void Look() const;
};