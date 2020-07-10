#pragma once
#include <vector>
#include "Creature.h"

using namespace std;

class Room;
class Item;
class Container;
class Consumable;

//Player class, has the most overrides for Creature methods because of the implicatons that user input imply
class Player : public Creature {
public:
	Player(World* world, const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int h, int mh, int ba_m, int ba_M, int bd_m, int bd_M, int c_m, int c_M, bool canDie = true);
	~Player();

	Room* GetRoom() const;
	bool IsAlive() const;
	void Look() const;
	void LookSelf() const;
	void CheckInventory() const;
	void Go(const char*dir);
	void Drop(const vector<string> args);
	void Consume(const vector<string>args);
};
