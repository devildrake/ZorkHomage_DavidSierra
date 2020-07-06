#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Exit.h"

Player::Player(const char* name, const char* desc, Room* initialRoom) : Creature(name, desc, initialRoom) {
	type = EntityType::PLAYER;
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
bool Player::IsPlayerInRoom() const {
	return false;
}

bool Player::IsAlive() const {
	return false;
}

void Player::Go(const char* dir) {
	Exit* e = GetRoom()->GetExitInDirection(dir);
	if (e != nullptr) {
		if (e->direction == Exit::StringToDirection(dir)) {
			SetNewParent(e->to);
		} else if (e->GetReverseDirection() == Exit::StringToDirection(dir)) {
			SetNewParent(e->from);
		}
		cout << parent->name << endl;
		cout << parent->description << endl;
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
