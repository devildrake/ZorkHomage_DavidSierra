#include "Room.h"

Room::Room(const char* name, const char* desc) :Entity(name, desc, nullptr) {

}

Room::~Room() {

}

void Room::Look() const {
	cout << name << endl << description << endl;
	//To Do call each of the entitiesContained (except player) Look() method

	//for (size_t i = 0; i < entitiesContained.size(); i++)
	//{
	//	
	//}
}