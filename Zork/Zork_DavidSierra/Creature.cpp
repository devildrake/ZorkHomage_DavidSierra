#include "Creature.h"
#include "Room.h"
#include "Container.h"
Creature::Creature(const char* name, const char* desc, Room* initialRoom, int maxHealth, int startingHealth) :Entity(name, desc, (Entity*)initialRoom) {
	this->name = name;
	description = desc;
	this->parent = (Entity*)initialRoom;
	this->parent->entitiesContained.push_back(this);
	max_health = maxHealth;
	health = startingHealth;
}

Creature::Creature(const char* name, const char* desc, Room* initialRoom) :Entity(name, desc, (Entity*)initialRoom) {
	max_health = DEFAULT_MAX_HEALTH;
	health = DEFAULT_MAX_HEALTH;
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
			if (eToTake->type == EntityType::ENTITY || eToTake->type == EntityType::ITEM || (eToTake->type == EntityType::CONTAINER && ((Container*)eToTake)->pickeable)) {
				eToTake->SetNewParent(this);
				Println(name + " took " + eToTake->name);
			} else {
				Println(name + " can't pick " + eToTake->name);
			}
		}
	} else if (args.size() == 4) {
		Entity* eToTakeFrom = GetRoom()->GetChildNamed(args[3].c_str());
		if (eToTakeFrom != nullptr) {
			if (eToTakeFrom->type == EntityType::CONTAINER) {
				if (!((Container*)eToTakeFrom)->isLocked) {
					Entity* eToTake = eToTakeFrom->GetChildNamed(args[1].c_str());
					if (eToTake != nullptr) {
						if (eToTake->type == EntityType::ENTITY || eToTake->type == EntityType::ITEM || (eToTake->type == EntityType::CONTAINER && ((Container*)eToTake)->pickeable)) {
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
				if (eToDropInto->type == EntityType::CONTAINER) {
					if (!((Container*)eToDropInto)->isLocked) {
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
				if (entityToOpen->type == EntityType::CONTAINER) {
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
