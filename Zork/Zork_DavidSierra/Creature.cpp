#include "Creature.h"
#include "Room.h"
#include "Container.h"
#include "Equipable.h"
#include "Consumable.h"
#include "Exit.h"

Creature::Creature(const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int maxHealth, int startingHealth, int baseAttack_m, int baseAttack_M, int baseDefense_m, int baseDefense_M, int critChances, int missChances, bool canDie) :Entity(name, desc, (Entity*)initialRoom) {
	this->name = name;
	description = desc;
	this->parent = (Entity*)initialRoom;
	//this->parent->entitiesContained.push_back(this);
	max_health = maxHealth;
	health = startingHealth;
	baseAttack.first = baseAttack_m;
	baseAttack.second = baseAttack_M;
	baseDefense.first = baseDefense_m;
	baseDefense.second = baseDefense_M;
	this->critChances = critChances;
	this->missChances = missChances;
	this->unArmedWeapon = unArmedWeapon;
	this->canDie = canDie;
	entityType = EntityType::CREATURE;
}

void Creature::UnEquip(const vector<string>args) {
	Entity* objectToUnEquip = GetChildNamed(args[1].c_str());

	if (objectToUnEquip != nullptr) {
		if (objectToUnEquip->entityType == EntityType::ITEM) {
			Item* itemToUnEquip = (Item*)(objectToUnEquip);
			switch (itemToUnEquip->itemType) {
			case ItemType::ARMOUR: {
				Equipable* equipableToEquip = ((Equipable*)itemToUnEquip);
				if (armour != nullptr) {
					UnEquip(armour);
					armour = nullptr;
					Println(name + " unequipped " + armour->name);
				} else {
					Println(name + " doesn't have " + itemToUnEquip->name + " equipped...");
				}
			}
			case ItemType::WEAPON: {
				Equipable* equipableToEquip = ((Equipable*)itemToUnEquip);
				if (weapon != nullptr) {
					UnEquip(weapon);
					weapon = nullptr;
					Println(name + " unequipped " + weapon->name);
				} else {
					Println(name + " doesn't have " + itemToUnEquip->name + " equipped...");
				}
				break;
			}default: {
				Println(name + " can't unequip " + itemToUnEquip->name);
				break;
			}
			}
		} else {
			Println(name + " can't unequip " + objectToUnEquip->name);
		}
	} else {
		Println(name + " doesn't own " + args[1]);

	}
}

void Creature::UnEquip(Equipable* eq) {
	bonusAttack.first -= eq->attack_bonus.first;
	bonusAttack.second -= eq->attack_bonus.second;
	bonusDefense.first -= eq->defense_bonus.first;
	bonusDefense.second -= eq->defense_bonus.second;
}

void Creature::Equip(Equipable* e) {
	bonusAttack.first += e->attack_bonus.first;
	bonusAttack.second += e->attack_bonus.second;
	bonusDefense.first += e->defense_bonus.first;
	bonusDefense.second += e->defense_bonus.second;
}

void Creature::Equip(const vector<string>args) {
	Entity* objectToEquip = GetChildNamed(args[1].c_str());
	if (objectToEquip != nullptr) {
		if (objectToEquip->entityType == EntityType::ITEM) {
			Item* itemToEquip = ((Item*)objectToEquip);

			switch (itemToEquip->itemType) {
			case ItemType::ARMOUR: {
				Equipable* equipableToEquip = ((Equipable*)itemToEquip);
				if (armour != equipableToEquip) {
					if (armour != nullptr) {
						UnEquip(armour);
					}
					Equip(equipableToEquip);
					armour = equipableToEquip;
					Println(name + " equipped " + armour->name);
				} else {
					Println(name + " has " + armour->name + " already equipped");
				}
				break;
			}
			case ItemType::WEAPON: {
				Equipable* equipableToEquip = ((Equipable*)itemToEquip);
				if (weapon != equipableToEquip) {
					if (weapon != nullptr) {
						UnEquip(weapon);
					}
					Equip(equipableToEquip);
					weapon = equipableToEquip;
					Println(name + " equipped " + weapon->name + " as weapon");
				} else {
					Println(name + " has " + weapon->name + " already equipped");
				}
				break;
			}default: {
				Println(name + " can't equip " + itemToEquip->name);
				break;
			}
			}
		} else {
			Println(name + " can't equip " + objectToEquip->name);
		}
	} else {
		Println(name + " doesn't own" + objectToEquip->name);
	}
}

void Creature::Inspect()const {
	Println("==========================");
	Println(name + (IsAlive() ? (IsStunned() ? " (Stunned)" : "") : (canDie ? " (Dead)" : "(unconscious")));
	if (IsAlive()) {
		cout << " - Health:" << health << "/" << max_health << endl
			<< " - Attack:" << baseAttack.first + bonusAttack.first << " - " << baseAttack.second + bonusAttack.second << (weapon == nullptr ? "" : " with " + weapon->name + " equipped as weapon") << endl
			<< " - Defense:" << baseDefense.first + bonusDefense.first << " - " << baseDefense.second + bonusDefense.second << (armour == nullptr ? "" : " with " + weapon->name + " equipped as armour") << endl;
	}
}

Creature::~Creature() {

}

Room* Creature::GetRoom() const {
	return (Room*)parent;
}

void Creature::Look()const {
	Println(name + (IsAlive() ? "" : " (Dead)"));
	Println(description);
}

int Creature::GetRandomAttack()const {
	int minDamage = (baseAttack.first + bonusAttack.first);
	int maxDamage = (baseAttack.second + bonusAttack.second);
	return (maxDamage != minDamage) ? (rand() % (maxDamage - minDamage) + minDamage) : minDamage;
}

int Creature::GetRandomDefense()const {
	if (baseDefense.first + bonusDefense.first > 0) {
		int minDefense = (baseDefense.first + bonusDefense.first);
		int maxDefense = (baseDefense.second + bonusDefense.second);
		int defDiff = maxDefense - minDefense;
		if (defDiff > 0) {
			return ((rand() % (defDiff)) + minDefense);
		} else {
			return minDefense;
		}
	}
	return 0;
}

void Creature::GetHurt(const int dmg) {
	int dmgToReceive = dmg - GetRandomDefense();

	if (dmgToReceive > 0) {
		health -= dmgToReceive;
		cout << name << " took " << dmgToReceive << " damage!\n";
	} else {
		Println(name + " took no damage!");
	}
}

void Creature::GetHurt(Creature* byWhom, bool critical) {
	int incomingDamage = byWhom->GetRandomAttack()*(critical ? 2 : 1);

	GetHurt(incomingDamage);

	if (critical) {
		stunnedTurnsRemaining = 3;
		Println(name + " is stunned!");
	}

	if (!IsAlive()) {
		string deathMessage = name + (canDie ? " died " : " became unconscious ");

		if (entitiesContained.size() > 0) {
			deathMessage += "and dropped:";
		}

		vector<string>itemsToDrop;
		for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it) {
			Entity* e = *it;
			itemsToDrop.push_back(e->name);
			deathMessage += "\n - " + e->name;

		}
		Drop(itemsToDrop);
		Println(deathMessage);
	}
}

//This method generates an "attack" towards combat_target, without further retribution
void Creature::CounterStrike() {
	if (combat_target != nullptr) {
		if (combat_target->IsAlive()) {
			if ((rand() % 100) > missChances) {
				bool isCritical = (rand() % 100) <= critChances;
				Println(name + " swings his " + (weapon == nullptr ? unArmedWeapon : weapon->name) + " and lands a" + (isCritical ? " CRITICAL " : " ") + "hit on " + combat_target->name + "!");
				combat_target->GetHurt(GetRandomAttack() * isCritical ? 2 : 1);
			} else {
				Println(name + " tried to attack " + combat_target->name + " but his " + (weapon == nullptr ? unArmedWeapon : weapon->name) + " missed!");
			}
		} else {
			combat_target = nullptr;
		}
	}
}

void Creature::TeleTransportToRoom(const Entity* targetRoomAsEntity) {
	if (targetRoomAsEntity->entityType == EntityType::ROOM) {
		Room* targetRoom = (Room*)targetRoomAsEntity;
		if (targetRoom != nullptr) {
			SetNewParent(targetRoom);
		}
	}
}


bool Creature::GoToRoom(const Entity* targetRoomAsEntity) {
	vector<Entity*> exits = parent->GetChildrenOfType(EntityType::EXIT);
	Room* targetRoom = (Room*)targetRoomAsEntity;
	if (exits.size() > 0) {
		for (vector<Entity*>::const_iterator it = exits.begin(); it != exits.cend(); ++it) {
			Exit* e = (Exit*)*it;
			if (e->to == targetRoom || e->from == targetRoom) {
				SetNewParent(targetRoom);
				return true;
			}
		}
	}
	return false;
}


bool Creature::IsStunned()const {
	return stunnedTurnsRemaining > 0;
}

//This method makes Creature go to the room of its combat_target if it is one exit away
void Creature::ChaseAttacker() {
	if (combat_target->parent != parent) {
		if (GoToRoom(combat_target->parent)) {
			cout << name << " chased " << combat_target->name << " to " << parent->name << endl;
		} else {
			combat_target = nullptr;
		}
	}
}

bool Creature::IsPlayerInRoom() const {
	for (list<Entity*>::const_iterator it = GetRoom()->entitiesContained.begin(); it != GetRoom()->entitiesContained.cend(); ++it) {
		if ((*it)->entityType == EntityType::PLAYER) {
			return true;
		}
	}
	return false;
}

//This method is the resolution of what would be considered an "action turn" by a Creature (not the player)
void Creature::TakeAction() {
	if (!IsAlive())return;
	if (combat_target != nullptr && !IsStunned()) {
		ChaseAttacker();
		TryToAttack(combat_target);
	}
	bool wasStunned = stunnedTurnsRemaining > 0;
	stunnedTurnsRemaining = wasStunned ? stunnedTurnsRemaining - 1 : 0;

	if (IsStunned()) {
		if (IsPlayerInRoom()) {
			Println(name + " is still stunned\n");
		}
	} else if (wasStunned) {
		if (IsPlayerInRoom()) {
			Println(name + " is no longer stunned\n");
		} else {
			Println("A loud roar is heard from miles away, " + name + " is no longer stunned");
		}
	}
}

//This method randomizes missed attacks and critical attacks and outputs corresponding texts
void Creature::TryToAttack(Creature* target) {
	target->combat_target = this;

	if ((rand() % 100) > missChances) {
		bool isCritical = (rand() % 100) <= critChances;

		Println(name + " swings his " + (weapon == nullptr ? unArmedWeapon : weapon->name) + " and lands a" + (isCritical ? " CRITICAL " : " ") + "hit on " + target->name + "!");
		target->GetHurt(this, isCritical);

	} else {
		Println(name + " tried to attack " + target->name + " but his " + (weapon == nullptr ? unArmedWeapon : weapon->name) + " missed!");
	}
	if (target->IsAlive() && !target->IsStunned()) {
		target->CounterStrike();
	}
}


void Creature::Attack(const vector<string> args) {
	Entity* attackTarget = GetRoom()->GetChildNamed(args[1].c_str());
	if (attackTarget != nullptr) {
		if (attackTarget->entityType == EntityType::CREATURE || attackTarget->entityType == EntityType::PLAYER) {
			Creature* creatureToAttack = (Creature*)attackTarget;
			if (creatureToAttack != this) {
				if (creatureToAttack->IsAlive()) {
					combat_target = creatureToAttack;
					TryToAttack(creatureToAttack);
				} else {
					Println(creatureToAttack->canDie ? "Leave the dead be" : "Leave the unconscious be");
				}
			}
		}
	}
}

void Creature::Take(const vector<string>args) {
	if (args.size() == 2) {
		Entity* eToTake = GetRoom()->GetChildNamed(args[1].c_str());
		if (eToTake != nullptr) {
			if (eToTake->entityType == EntityType::ENTITY || eToTake->entityType == EntityType::ITEM || (eToTake->entityType == EntityType::CONTAINER && ((Container*)eToTake)->pickeable)) {
				eToTake->SetNewParent(this);
				Println(name + " took " + eToTake->name);
			} else {
				Println(name + " can't pick " + eToTake->name);
			}
		} else {
			Println(name + " found no " + args[1] + " to be picked");
		}
	} else if (args.size() == 4) {
		Entity* eToTakeFrom = GetRoom()->GetChildNamed(args[3].c_str());
		if (eToTakeFrom != nullptr) {
			if (eToTakeFrom->entityType == EntityType::CONTAINER) {
				if (!((Container*)eToTakeFrom)->isLocked) {
					Entity* eToTake = eToTakeFrom->GetChildNamed(args[1].c_str());
					if (eToTake != nullptr) {
						if (eToTake->entityType == EntityType::ENTITY || eToTake->entityType == EntityType::ITEM || (eToTake->entityType == EntityType::CONTAINER && ((Container*)eToTake)->pickeable)) {
							eToTake->SetNewParent(this);
							Println(name + " took " + eToTake->name + " from " + eToTakeFrom->name);
						} else {
							Println(name + " can't pick " + eToTake->name);
						}
					} else {
						Println(name + " couldn't find " + args[1] + " inside " + eToTakeFrom->name);
					}
				} else {
					Println(name + " couldn't open " + eToTakeFrom->name);
				}
			} else {
				Println(name + " can't pick " + eToTakeFrom->name);
			}
		} else {
			Println("there is no " + args[3]);
		}
	}
}


void Creature::Drop(const vector<string>args) {
	if (args.size() == 1) {
		Entity* eToDrop = GetChildNamed(args[0].c_str());
		if (eToDrop != nullptr) {
			if (armour == eToDrop) {
				UnEquip(armour);
				armour = nullptr;
			} else if (weapon == eToDrop) {
				UnEquip(weapon);
				weapon = nullptr;
			}
			eToDrop->SetNewParent(GetRoom());
		}
	} else if (args.size() == 2) { //Drop on current room
		Entity* eToDrop = GetChildNamed(args[1].c_str());
		if (eToDrop != nullptr) {
			if (armour == eToDrop) {
				UnEquip(armour);
				armour = nullptr;
			} else if (weapon == eToDrop) {
				UnEquip(weapon);
				weapon = nullptr;
			}
			eToDrop->SetNewParent(GetRoom());
			Println(name + " dropped " + eToDrop->name);
		} else {
			Println(name + " doesn't have " + args[1] + " in his inventory");
		}
	} else if (args.size() == 4) { //Try to drop into something
		Entity* eToDropInto = GetRoom()->GetChildNamed(args[3].c_str());
		if (eToDropInto != nullptr) {
			Entity* eToDrop = GetChildNamed(args[1].c_str());
			if (eToDrop != nullptr) {
				if (eToDropInto->entityType == EntityType::CONTAINER) {
					if (!((Container*)eToDropInto)->isLocked) {
						if (armour == eToDrop) {
							UnEquip(armour);
							armour = nullptr;
						} else if (weapon == eToDrop) {
							UnEquip(weapon);
							weapon = nullptr;
						}
						eToDrop->SetNewParent(eToDropInto);
						Println(name + " put " + eToDrop->name + " inside " + eToDropInto->name);
					} else {
						Println(name + "couldn't put " + eToDrop->name + " inside " + eToDropInto->name + " (" + eToDropInto->name + " is locked)");
					}
				} else if (eToDropInto->entityType == EntityType::CREATURE) {
					if (armour == eToDrop) {
						UnEquip(armour);
						armour = nullptr;
					} else if (weapon == eToDrop) {
						UnEquip(weapon);
						weapon = nullptr;
					}
					eToDrop->SetNewParent(eToDropInto);
					Println(name + " put " + eToDrop->name + " inside " + eToDropInto->name);

				} else {
					Println(name + "couldn't put " + eToDrop->name + " inside " + eToDropInto->name + " (" + eToDropInto->name + " is not a container)");
				}
			} else {
				Println(name + " doesn't have " + args[1] + " in his inventory");
			}
		}
	}
}


void Creature::UnLock(const vector<string> args) {
	if (args.size() == 4) {
		Entity* objToOpenWith = GetChildNamed(args[3].c_str());
		if (objToOpenWith != nullptr) {
			Entity* entityToOpen = (Entity*)GetRoom()->GetChildNamed(args[1].c_str());
			if (entityToOpen != nullptr) {
				if (entityToOpen->entityType == EntityType::CONTAINER) {
					Container* containerToOpen = (Container*)entityToOpen;
					if (containerToOpen->keyToUnlock != nullptr && containerToOpen->isLocked) {
						if ((containerToOpen)->keyToUnlock == objToOpenWith) {
							containerToOpen->isLocked = false;
							Println(name + " used " + objToOpenWith->name + " to open " + entityToOpen->name);
							//containerToOpen->keyToUnlock = nullptr;
							//delete key?
						} else {
							Println(name + " couldn't use " + objToOpenWith->name + " to open " + entityToOpen->name + (" (Wrong key)"));
						}
					} else {
						Println(name + " couldn't unlock " + entityToOpen->name + " (Not locked ) ");
					}
				} else if (entityToOpen->entityType == EntityType::EXIT) {
					Exit* exitToOpen = (Exit*)entityToOpen;
					if (exitToOpen->keyToUnlock != nullptr && exitToOpen->isLocked) {
						if ((exitToOpen)->keyToUnlock == objToOpenWith) {
							exitToOpen->isLocked = false;
							Println(name + " used " + objToOpenWith->name + " to open " + entityToOpen->name);
							//containerToOpen->keyToUnlock = nullptr;
							//delete key?
						} else {
							Println(name + " couldn't use " + objToOpenWith->name + " to open " + entityToOpen->name + (" (Wrong key)"));
						}
					} else {
						Println(name + " couldn't unlock " + entityToOpen->name + " (Not locked ) ");
					}
				} else {
					Println(name + " can't unlock " + entityToOpen->name);
				}
			} else {
				Println(name + " couldn't find " + args[1]);
			}
		} else {
			Println(name + " doesn't have " + args[3] + " in his inventory");
		}
	}
}

bool Creature::IsAlive() const {
	return health > 0;
}
