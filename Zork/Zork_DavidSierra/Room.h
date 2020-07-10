#pragma once
#include "Entity.h"
#include <vector>
class Exit;

//Entity type that has no parent whatsoever and works as the "place" where other entities "are"
class Room :public Entity {
public:
	Room(World* world, const char* name, const char* desc);
	~Room();
	void Look() const;
	bool playerInRoom;
	Exit* GetExitInDirection(const char* dir) const;
};