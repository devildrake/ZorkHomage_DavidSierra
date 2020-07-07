#include "Exit.h"
#include "Room.h"
#include "GlobalMethods.h"

Exit::Exit(const char* name, const char* desc, const char* auxName, const char* auxDesc, Exit::Direction aDirection, Room* from, Room* to) : Entity(name, desc, nullptr) {
	direction = aDirection;
	this->from = from;
	this->to = to;
	this->auxName = auxName;
	this->auxDescription = auxDescription;
	from->entitiesContained.push_back(this);
	to->entitiesContained.push_back(this);
	entityType = EntityType::EXIT;
}

Exit::~Exit() {
	//if (from != nullptr) {
	//	from->entitiesContained.remove(this);
	//} else {
	//	to->entitiesContained.remove(this);
	//}
}

void Exit::Look() const {
	if (from->playerInRoom) {
		cout << "that " << DirectionToStringNarrative(direction) << " there's a " + name + " - " + description + " that leads to " + to->name << endl;
	} else {
		cout << "that " << DirectionToStringNarrative(GetReverseDirection()) << " there's a " + auxName + " - " + auxDescription + " that leads to " + from->name << endl;
	}
}

string Exit::DirectionToStringNarrative(const Direction dir) {
	switch (dir) {
	case Direction::DOWN: {
		return "downwards";
		break;
	}	case Direction::UP: {
		return "upwards";
		break;
	}	case Direction::NORTH: {
		return "to the north";
		break;
	}	case Direction::SOUTH: {
		return "to the south";
		break;
	}	case Direction::EAST: {
		return "to the east";
		break;
	}	case Direction::WEST: {
		return "to the west";
		break;
	}default:
		return "";
		break;
	}
}

Exit::Direction Exit::StringToDirection(const char* dirString) {
	bool found = false;
	Exit::Direction res = Exit::Direction::NONE;
	for (int8_t i = 0; i < (int8_t)(Exit::Direction::NONE) && !found; ++i) {
		if (CompareStrings(dirString, directionStrings[i])) {
			found = true;
			res = (Exit::Direction)i;
		}
	}
	return res;
}
Exit::Direction Exit::GetReverseDirection()const {
	if (direction == Direction::NONE)return Direction::NONE;
	return (Direction)((((int)direction) + 3) % 6);
}
