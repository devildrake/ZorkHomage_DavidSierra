#pragma once
#include "Container.h"

class World;
class Room;

class Cart :public Container {
	Entity* itemToBePlaced;
public:
	Cart(World* world, const char* name, const char* desc, Room* initialRoom, Entity* itemToBePlaced);
	~Cart();
	void TakeAction();
};