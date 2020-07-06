#include "Exit.h"
#include "Room.h"
#include "GlobalMethods.h"

Exit::Exit(const char* name, const char* desc, Exit::Direction aDirection, Room* from, Room* to) : Entity(name, desc, nullptr) {
	this->direction = direction;
	this->from = from;
	this->to = to;
	from->entitiesContained.push_back(this);
	to->entitiesContained.push_back(this);
	type = EntityType::EXIT;
}

Exit::~Exit() {

}



void Exit::Look() const {
	cout << description + " that leads to " + to->name << endl;
}

Exit::Direction Exit::StringToDirection(const char* dirString) {
	bool found = false;
	Exit::Direction res = Exit::Direction::NONE;
	for (int8_t i = 0; i < (int8_t)4 && !found; ++i) {
		if (CompareStrings(dirString, directionStrings[i])) {
			found = true;
			res = (Exit::Direction)i;
		}
	}
	return res;
}
Exit::Direction Exit::GetReverseDirection()const {
	Direction res = Direction::NONE;
	switch (direction) {
	case Direction::EAST: {
		res = Direction::WEST;
		break;
	}
	case Direction::WEST: {
		res = Direction::EAST;

		break;
	}
	case Direction::NORTH: {
		res = Direction::SOUTH;

		break;
	}
	case Direction::SOUTH: {
		res = Direction::NORTH;
		break;
	}
	}
	return res;
}
