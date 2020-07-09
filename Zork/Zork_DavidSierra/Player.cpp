#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Exit.h"

Player::Player(const char* name, const char* desc, const char* unArmedWeapon, Room* initialRoom, int health, int maxHealth, int bAtt_m, int bAtt_M, int bDef_m, int bDef_M, int crit, int miss) : Creature(name, desc, unArmedWeapon, initialRoom, health, maxHealth, bAtt_m, bAtt_M, bDef_m, bDef_M, crit, miss) {
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
	return false;
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
