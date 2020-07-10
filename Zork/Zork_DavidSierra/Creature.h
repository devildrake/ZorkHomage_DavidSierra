#pragma once
#include "Entity.h"
#include <vector>
using namespace std;

class Room;
class Equipable;
class Item;
class Exit;
#define DEFAULT_MAX_HEALTH 25;

//Entity type from which all "living" beings inherit
class Creature : public Entity {
protected:
	int critChances, missChances;
	int stunnedTurnsRemaining;
	pair<int, int> baseAttack;
	pair<int, int> baseDefense;
	pair<int, int> bonusAttack;
	pair<int, int> bonusDefense;
	void CheckDeath();
public:
	Creature(World* world, const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int baseAttack_m, int baseAttack_M, int baseDefense_m, int baseDefense_M, int critChances, int missChances, bool canDie = true);
	~Creature();
	Room* GetRoom() const;
	bool canDie;
	const char* unArmedWeapon;
	bool IsAlive() const;
	bool IsStunned()const;
	bool GoToRoom(const Entity* targetRoomAsEntity);
	void TeleTransportToRoom(const Entity* targetRoomAsEntity);
	bool IsPlayerInRoom() const;
	int GetRandomDefense()const;
	int GetRandomAttack()const;
	int max_health;
	int health;
	void Look() const;
	void Take(const vector<string> args);
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
	virtual void Drop(const vector<string> args);
	virtual void Consume(const vector<string> args);
	virtual void TakeAction();
	void GetHurt(Creature* byWhom, bool critical);
	void GetHurt(const int dmg);
	Creature* combat_target;
	Equipable* weapon;
	Equipable* armour;
};