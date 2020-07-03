#pragma once
#include "Entity.h"
class Room :public Entity {
public:
	Room(const char* name, const char* desc);
	~Room();
	void Look() const;
};