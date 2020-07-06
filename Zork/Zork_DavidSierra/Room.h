#pragma once
#include "Entity.h"
#include <vector>
class Exit;

class Room :public Entity {
public:
	Room(const char* name, const char* desc);
	~Room();
	void Look() const;
	Exit* GetExitInDirection(const char* dir) const;
};