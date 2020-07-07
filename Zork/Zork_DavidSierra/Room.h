#pragma once
#include "Entity.h"
#include <vector>
class Exit;

class Room :public Entity {
public:
	Room(const char* name, const char* desc);
	~Room();
	void Look() const;
	bool playerInRoom;
	Exit* GetExitInDirection(const char* dir) const;
};