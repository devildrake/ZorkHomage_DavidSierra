#include "World.h"
#include <iostream>
#include "GlobalMethods.h"
#include "Entity.h"
#include "Creature.h"
#include "Item.h"
#include "Exit.h"
#include "Room.h"
#include "Player.h"

const string lookCmds[3] = { "look","l","mirar" };
const string lookPpsts[3] = { "at","a","hacia" };

World::World() {
	Room* forest = new Room("Forest", "A beautiful forest that seems neverending");
	player = new Player("Sheldor", "You seem like a fine fella", forest);
	rooms.push_back(forest);
	cout << "Welcome to a Zork homage by David Sierra! - Version 0.0.1\n";
}

World::~World() {
	//Delete player
	delete player;

	//Iterate rooms and delete them
	vector<Room*>::iterator it;
	int i = 0;
	for (it = rooms.begin(); it != rooms.end(); it++, i++) {
		delete rooms[i];
	}
}

bool World::TryParseCommand(vector<string>& args) {

	bool res = true;

	switch (args.size()) {
	case 1: {//Plain commands

		//LOOK
		if (CompareStrings(args[0], lookCmds)) {
			//To Do Player Must "Look around and print all he "is able to see" in the current room, which means making a call to the current rooms Look method 
			//player->Look();
			player->Look();
		}
		else {
			res = false;
		}
		break;
	}
	case 2: {//"Command" + EntityName
		//LOOK
		if (CompareStrings(args[0], lookCmds)) {
			//To do Must call entities' Look() override if entity with name arg[1] is found 
			//Check Parent's containingEntities? 
		//player->Look();
		}
		else {
			res = false;
		}
		break;
	}
	case 3: {
		//LOOK 
		if (CompareStrings(args[0], lookCmds)) {
			if (CompareStrings(args[1], lookPpsts)) {
				//To do Must call entities' Look() override if entity with name arg[2] is found (Only works with one of the correct prepositions)
			}
		}
		else {
			res = false;
		}
		break;
	}
	case 4: {// "Command" + EntityName + "From" + EntityName

		//LOOK 
		if (CompareStrings(args[0], lookCmds)) {
			if (CompareStrings(args[1], lookPpsts)) {
				//To do Must call entities' Look() override if entity with name arg[1] is found (Only works with one of the correct prepositions)
				//Check Parent's containingEntities?
			}
		}
		else {
			res = false;
		}
		break;
	}
	default:
		res = false;
	}

	return res;
}
