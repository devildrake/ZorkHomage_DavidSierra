#pragma once
#include "Entity.h"
using namespace std;

class Room;

const string directionStrings[4] = { "north","south","west","east" };

class Exit :public Entity {

public:
	enum Direction { NORTH, SOUTH, WEST, EAST, NONE };
	Direction direction;
	Room* from;
	Room* to;
	static Direction StringToDirection(const char* dirString);
	Direction GetReverseDirection()const;
	Exit(const char*name, const char* desc, Direction aDirection, Room*, Room*);
	~Exit();
	void Look() const;
};