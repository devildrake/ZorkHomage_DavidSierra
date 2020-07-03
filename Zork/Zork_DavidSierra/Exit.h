#pragma once
#include "Entity.h"
using namespace std;

class Room;

class Exit :public Entity {

public:
	enum Direction { NORTH, SOUTH, WEST, EAST };
	Direction direction;
	Room* from;
	Room* to;
	Exit(const char*name, const char* desc, Room* , Room* );
	~Exit();
	void Look() const;
};