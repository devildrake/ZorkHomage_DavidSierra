#include "Exit.h"
#include "Room.h"
#include "GlobalMethods.h"

Exit::Exit(World* world, const char* name, const char* desc, const char* auxName, const char* auxDesc, Exit::Direction aDirection, Room* from, Room* to, bool uniDirectional, Entity* key) : Entity(world, name, desc, nullptr) {
	direction = aDirection;
	this->from = from;
	this->to = to;
	this->auxName = auxName;
	this->auxDescription = auxDescription;
	this->uniDirectional = uniDirectional;
	from->entitiesContained.push_back(this);
	to->entitiesContained.push_back(this);

	if (key != nullptr) {
		isLocked = true;
		this->keyToUnlock = key;
	}
	entityType = EntityType::EXIT;
}

Exit::~Exit() {

}

void Exit::Look() const {
	if (from->playerInRoom) {
		cout << "that " << DirectionToStringNarrative(direction) << " there's " << GetPreferredArticle(name) << " " << name + (description.size() > 0 ? " " + description : "") + (isLocked ? "that is locked" : " that leads to " + to->name) << endl;
	} else if (!uniDirectional) {
		cout << "that " << DirectionToStringNarrative(GetReverseDirection()) << " there's " << GetPreferredArticle(auxName) << " " << auxName + (auxDescription.size() > 0 ? " " + auxDescription : "") + (isLocked ? "that is locked" : " that leads to " + from->name) << endl;
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
