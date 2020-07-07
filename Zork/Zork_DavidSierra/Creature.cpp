#include "Creature.h"
#include "Room.h"
#include "Container.h"
#include "Equipable.h"
#include "Consumable.h"

Creature::Creature(const char* name, const char* desc, Room* initialRoom, int maxHealth, int startingHealth, int baseAttack_m, int baseAttack_M, int baseDefense_m, int baseDefense_M) :Entity(name, desc, (Entity*)initialRoom) {
	this->name = name;
	description = desc;
	this->parent = (Entity*)initialRoom;
	this->parent->entitiesContained.push_back(this);
	max_health = maxHealth;
	health = startingHealth;
	baseAttack.first = baseAttack_m;
	baseAttack.second = baseAttack_M;
	baseDefense.first = baseDefense_m;
	baseDefense.second = baseDefense_M;
	entityType = EntityType::CREATURE;
}

void Creature::UnEquip(vector<string>args) {
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

void Creature::Equip(vector<string>args) {
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
	Println(name);
	cout << " -Health:" << health << "/" << max_health << endl
		<< " -Attack:" << baseAttack.first + bonusAttack.first << " - " << baseAttack.second + bonusAttack.second << endl
		<< " -Defense:" << baseDefense.first + bonusDefense.first << " - " << baseDefense.second + bonusDefense.second << endl;
}

Creature::~Creature() {

}

Room* Creature::GetRoom() const {
	return (Room*)parent;
}

void Creature::Look()const {
	cout << name << endl;
	cout << description << endl;
}

void Creature::Take(vector<string>args) {
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
	} else {

	}
	//Entity* eToTake = GetRoom()->GetChildNamed(name);
	//if (eToTake != nullptr) {
	//	eToTake->SetNewParent(this);
	//}
}

void Creature::Drop(vector<string>args) {
	if (args.size() == 2) { //Drop on current room
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
				} else {
					Println(name + "couldn't put " + eToDrop->name + " inside " + eToDropInto->name + " (" + eToDropInto->name + " is not a container)");
				}
			} else {
				Println(name + " doesn't have " + args[1] + " in his inventory");
			}
		}
	}
}


void Creature::UnLock(vector<string> args) {
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
				} else {
					Println(name + " couldn't unlock " + entityToOpen->name);
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
	return false;
}
