#pragma once
#include "Entity.h"
#include <vector>
using namespace std;

class Room;
class Equipable;
class Item;
class Exit;
#define DEFAULT_MAX_HEALTH 25;

class Creature : public Entity {
protected:
	int max_health, health;
	int critChances, missChances;
	int stunnedTurnsRemaining;
	pair<int, int> baseAttack;
	pair<int, int> baseDefense;
	pair<int, int> bonusAttack;
	pair<int, int> bonusDefense;
public:
	Creature(const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int, int, int, int, int, int, int, int);
	~Creature();
	Room* GetRoom() const;
	const char* unArmedWeapon;
	bool IsAlive() const;
	bool IsStunned()const;
	bool GoToRoom(const Entity* targetRoomAsEntity);
	bool IsPlayerInRoom() const;
	int GetRandomDefense()const;
	int GetRandomAttack()const;
	void Look() const;
	void Take(const vector<string> args);
	void Drop(const vector<string> args);
	void UnLock(const vector<string> args);
	void Equip(const vector<string> args);
	void Equip(Equipable* e);
	void UnEquip(const vector<string> args);
	void UnEquip(Equipable* e);
	void Inspect()const;
	void TryToAttack(Creature* target);
	void Attack(const vector<string> args);
	void CounterStrike();
	void ChaseAttacker();
	void TakeAction();
	void GetHurt(Creature* byWhom, bool critical);
	void GetHurt(const int dmg);
	Creature* combat_target;
	Equipable* weapon;
	Equipable* armour;
};