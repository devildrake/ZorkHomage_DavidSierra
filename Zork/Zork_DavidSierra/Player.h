#pragma once
#include <vector>
#include "Creature.h"

using namespace std;

class Room;
class Item;
class Container;

class Player : public Creature {
public:
	Player(const char* name, const char* desc, Room* initialRoom, int h, int mh, int ba_m, int ba_M, int bd_m, int bd_M);
	~Player();

	Room* GetRoom() const;
	bool IsPlayerInRoom() const;
	bool IsAlive() const;
	void Look() const;
	void LookSelf() const;
	void CheckInventory() const;
	void Go(const char*dir);
};
