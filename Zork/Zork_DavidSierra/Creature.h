#pragma once
#include "Entity.h"
#include <vector>
using namespace std;

class Room;
class Item;

#define DEFAULT_MAX_HEALTH 25;

class Creature : public Entity {
protected:
	int max_health;
	int health;
public:
	Creature(const char* name, const char* desc, Room* initialRoom, int, int);
	Creature(const char* name, const char* desc, Room* initialRoom);
	~Creature();

	bool IsAlive() const;
	void Look() const;
	void Take(vector<string>args);
	void Drop(vector<string>args);
	void UnLock(vector<string>args);
	Room* GetRoom() const;
	Creature* combat_target;
	Item* weapon;
	Item* armour;
};