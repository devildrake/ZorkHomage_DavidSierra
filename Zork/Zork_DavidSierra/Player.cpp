#include "Player.h"
#include "Room.h"
#include "Consumable.h"
#include "Container.h"
#include "Exit.h"

Player::Player(World* world, const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int health, int maxHealth, int bAtt_m, int bAtt_M, int bDef_m, int bDef_M, int crit, int miss, bool canDie) : Creature(world, name, desc, unArmedWeapon, initialRoom, health, maxHealth, bAtt_m, bAtt_M, bDef_m, bDef_M, crit, miss, canDie) {
	entityType = EntityType::PLAYER;
	GetRoom()->playerInRoom = true;
}

Player::~Player() {

}

void Player::LookSelf()const {
	Println(name + " - " + description);
}

void Player::Look() const {
	parent->Look();
}

Room* Player::GetRoom() const {
	return (Room*)parent;
}


bool Player::IsAlive() const {
	return health > 0;
}

void Player::Drop(vector<string >args) {
	if (args.size() == 1) {
		Entity* eToDrop = GetChildNamed(args[0].c_str());
		if (eToDrop != nullptr) {
			if ((Entity*)armour == eToDrop) {
				UnEquip(armour);
				armour = nullptr;
			} else if ((Entity*)weapon == eToDrop) {
				UnEquip(weapon);
				weapon = nullptr;
			}
			eToDrop->SetNewParent(GetRoom());
		}
	} else if (args.size() == 2) { //Drop on current room
		Entity* eToDrop = GetChildNamed(args[1].c_str());
		if (eToDrop != nullptr) {
			if ((Entity*)armour == eToDrop) {
				UnEquip(armour);
				armour = nullptr;
			} else if ((Entity*)weapon == eToDrop) {
				UnEquip(weapon);
				weapon = nullptr;
			}
			eToDrop->SetNewParent(GetRoom());
			if (IsAlive()) {
				Println(name + " dropped " + eToDrop->name);
			}
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
						if ((Entity*)armour == eToDrop) {
							UnEquip(armour);
							armour = nullptr;
						} else if ((Entity*)weapon == eToDrop) {
							UnEquip(weapon);
							weapon = nullptr;
						}
						eToDrop->SetNewParent(eToDropInto);
						Println(name + " put " + eToDrop->name + " inside " + eToDropInto->name);
					} else {
						Println(name + "couldn't put " + eToDrop->name + " inside " + eToDropInto->name + " (" + eToDropInto->name + " is locked)");
					}
				} else if (eToDropInto->entityType == EntityType::CREATURE) {
					if ((Entity*)armour == eToDrop) {
						UnEquip(armour);
						armour = nullptr;
					} else if ((Entity*)weapon == eToDrop) {
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

void Player::Consume(const vector<string>args) {
	Entity* entityToConsume = GetChildNamed(args[1].c_str());
	if (entityToConsume != nullptr) {
		if (entityToConsume->entityType == EntityType::ITEM) {
			Item* itemToConsume = (Item*)entityToConsume;
			if (itemToConsume != nullptr) {
				if (itemToConsume->itemType == ItemType::CONSUMABLE) {
					Consumable* consumable = (Consumable*)itemToConsume;
					if (consumable != nullptr) {
						consumable->BeConsumed();
					} else {
						Println(itemToConsume->name + " cannot be consumed");
					}
				} else {
					Println(itemToConsume->name + " cannot be consumed");
				}
			} else {
				Println(itemToConsume->name + " couldn't be found in inventory");
			}
		} else {
			Println(entityToConsume->name + " cannot be consumed");
		}
	} else {
		Println(entityToConsume->name + " couldn't be found in inventory");
	}
}


void Player::Go(const char* dir) {
	Exit* e = GetRoom()->GetExitInDirection(dir);
	if (e != nullptr) {
		if (!e->isLocked) {
			GetRoom()->playerInRoom = false;
			if (e->direction == Exit::StringToDirection(dir)) {
				SetNewParent(e->to);
				GetRoom()->playerInRoom = true;
				cout << parent->name << endl;
				cout << parent->description << endl;
			} else if (e->GetReverseDirection() == Exit::StringToDirection(dir)) {
				if (!e->uniDirectional) {
					SetNewParent(e->from);
					GetRoom()->playerInRoom = true;
					cout << parent->name << endl;
					cout << parent->description << endl;
				} else {
					Println("No path that way");
				}
			}
		} else {
			Println(e->name + " is locked");
		}
	}

}

void Player::CheckInventory() const {
	if (entitiesContained.size() > 0) {
		Println("You find these in your bag:");
		for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it) {
			Println(" - " + (*it)->name);
		}
	} else {
		Println("Your bag is empty");
	}
}
