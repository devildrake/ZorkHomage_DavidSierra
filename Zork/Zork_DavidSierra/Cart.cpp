#include "Cart.h"
#include "Room.h"
#include "World.h"

Cart::Cart(World* world, const char* name, const char* desc, Room* initialRoom, Entity* itemToBePlaced) :Container(world, name, desc, initialRoom) {
	this->itemToBePlaced = itemToBePlaced;
}

Cart::~Cart() {

}

void Cart::TakeAction() {
	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it) {
		if ((*it) == itemToBePlaced) {
			world->gameFinished = true;
		}
	}
}