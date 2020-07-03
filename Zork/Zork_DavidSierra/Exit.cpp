#include "Exit.h"
#include "Room.h"

Exit::Exit(const char* name, const char* desc, Room* from, Room* to) : Entity(name, desc, nullptr) {
	this->from = from;
	this->to = to;
}

Exit::~Exit() {	

}

void Exit::Look() const {
	cout << description + " that leads to " + to->name << endl;
}