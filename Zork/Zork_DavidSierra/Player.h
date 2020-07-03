#pragma once
#include <vector>
#include "Creature.h"

using namespace std;

class Room;
class Item;

class Player : public Creature {
public:
	Player(const char* name, const char* desc, Room* initialRoom);
	~Player();

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;
	void Look() const;
};
