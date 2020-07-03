#include "Player.h"
#include "Room.h"
#include "Item.h"

Player::Player(const char* name, const char* desc, Room* initialRoom) : Creature(name, desc, initialRoom) {

}

Player::~Player() {

}

void Player::Look() const {
	parent->Look();
}

Room* Player::GetRoom() const {
	return nullptr;
}
bool Player::PlayerInRoom() const {
	return false;
}
bool Player::IsAlive() const {
	return false;
}