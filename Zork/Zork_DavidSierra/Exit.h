#pragma once
#include "Entity.h"
using namespace std;

class Room;

const string directionStrings[6] = { "north","west","up","south","east","down" };

class Exit :public Entity {

public:
	enum Direction { NORTH, WEST, UP, SOUTH, EAST, DOWN, NONE };
	Direction direction;
	std::string auxName;
	std::string auxDescription;
	Room* from;
	Room* to;
	static Direction StringToDirection(const char* dirString);
	static string DirectionToStringNarrative(const Direction dir);
	bool uniDirectional, isLocked;
	Entity* keyToUnlock;
	Direction GetReverseDirection()const;
	Exit(const char*name, const char* desc, const char* auxName, const char* auxDesc, Direction aDirection, Room* from, Room*to, bool uniDirectional = false, Entity* key = nullptr);
	~Exit();
	void Look() const;
};