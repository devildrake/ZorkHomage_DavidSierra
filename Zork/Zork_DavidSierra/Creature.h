#pragma once
#include "Entity.h"
#include <vector>
using namespace std;

class Room;
class Equipable;

#define DEFAULT_MAX_HEALTH 25;

class Creature : public Entity {
protected:
	int max_health;
	int health;
	pair<int, int> baseAttack;
	pair<int, int> baseDefense;
	pair<int, int> bonusAttack;
	pair<int, int> bonusDefense;
public:
	Creature(const char* name, const char* desc, Room* initialRoom, int, int, int, int, int, int);
	~Creature();

	bool IsAlive() const;
	void Look() const;
	void Take(vector<string>args);
	void Drop(vector<string>args);
	void UnLock(vector<string>args);
	void Equip(vector<string>args);
	void Equip(Equipable* e);
	void UnEquip(vector<string>args);
	void UnEquip(Equipable* e);
	void Inspect()const;
	Room* GetRoom() const;
	Creature* combat_target;
	Equipable* weapon;
	Equipable* armour;
};