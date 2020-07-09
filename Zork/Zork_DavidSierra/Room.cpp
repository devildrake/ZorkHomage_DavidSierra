#include "Room.h"
#include "Exit.h"
#include "Creature.h"
Room::Room(const char* name, const char* desc) :Entity(name, desc, nullptr) {
	entityType = EntityType::ROOM;
}

Room::~Room() {

}

void Room::Look() const {
	cout << name << endl << description << endl;
	//To Do call each of the entitiesContained (except player) Look() method

	for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend(); ++it) {
		Entity* e = *it;

		switch (e->entityType) {
		case EntityType::NPC: {
			Println("You can see someone: " + e->name);
			break;
		}
		case EntityType::CREATURE: {
			Println("You can see something: " + e->name + (((Creature*)e)->IsAlive() ? "" : " (Dead)"));
			break;
		}
		case EntityType::PLAYER: {
			break;
		}
		case EntityType::EXIT: {
			Exit* exit = (Exit*)e;
			if (!exit->uniDirectional || this == exit->from) {
				cout << "You can see ";
				e->Look();
			}
			break;
		}
		default: {
			cout << "There is " << GetPreferredArticle(e->name) << " " << e->name << " here" << endl;
			break;
		}
		}


	}
}

Exit* Room::GetExitInDirection(const char* dir) const {
	//Input direction (string) is parsed to enum Direction 
	Exit* res = nullptr;
	Exit::Direction direction = Exit::StringToDirection(dir);
	if (direction != Exit::Direction::NONE) {
		for (list<Entity*>::const_iterator it = entitiesContained.begin(); it != entitiesContained.cend() && res == nullptr; ++it) {
			Entity* e = *it;
			if (e->entityType == EntityType::EXIT) {
				Exit* exit = (Exit*)e;

				if (exit->from == this) {
					if (exit->direction == direction) {
						res = exit;
					}
				} else {
					if (exit->GetReverseDirection() == direction) {
						res = exit;
					}
				}
			}
		}
	}
	if (res == nullptr) {
		Println("Didn't find an exit towards " + (string)dir);
	}
	return res;
}


//Exit* Room::GetExitToDirection(const char* dir)const {
//	Exit* res = nullptr;
//	//Exit* res = nullptr;
//	//for (vector<Room*>::iterator it = exits.begin(); it != exits.cend() && res == nullptr; ++it) {
//	//	res = *it;
//	//}
//	//return res;
//	return res;
//}


