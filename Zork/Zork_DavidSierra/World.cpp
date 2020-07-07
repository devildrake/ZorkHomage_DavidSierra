#include "World.h"
#include <iostream>
#include "GlobalMethods.h"
#include "Equipable.h"
#include "Container.h"
#include "Exit.h"
#include "Room.h"
#include "Player.h"
const string lookCmds[3] = { "look","l" };
const string lookPpsts[3] = { "at","to" };
const string goCmds[3] = { "go","walk","move" };
const string selfCmds[3] = { "me","self","myself" };
const string clearCmds[4] = { "clear","wipe","clr","cls" };
const string pickCmds[3] = { "pick","grab","take" };
const string inventoryCmds[3] = { "inventory", "inv","i" };
const string unlockCmds[2] = { "open", "unlock" };
const string equipCmds[2] = { "equip","eq" };
const string unEquipCmds[2] = { "unequip","uneq" };
const string examineCmds[4] = { "examine","ex","inspect","ins" };
const string dropCmds[2] = { "drop", "place" };


World::World() {
	Room* cabin = new Room("Small Cabin", "A small cabin in the woods, clearly owned by a hunter");

	Room* cabinOut = new Room("Outside of cabin", "You can see a small cabin made out of wood");

	Room* caveEntranceRoom = new Room("Cave Entrance", "A hole in the ground appears to lead toward a cave");

	Room* cave = new Room("Cave ", "A small cave lit by small holes on the walls");

	Room* forest = new Room("Forest", "A beautiful forest that seems neverending");

	Container* mailBox = new Container("Mailbox", "A rusty mailbox", forest);
	Entity* key = new Entity("Key", "A small key with a horse sigil carved", (Entity*)mailBox);
	Container* box = new Container("Box", "A small box with a horse sigil carved", forest, key);

	Entity* welcomeCard = new Entity("Note", "This is a note", (Entity*)mailBox);
	Equipable* dagger = new Equipable("Dagger", "A small rusty dagger", (Entity*)box, ItemType::WEAPON, pair<int, int>{3, 7}, pair<int, int>{1, 2});
	Entity* rock = new Entity("Rock", "An engraved rock that reads: Tavern (No monsters allowed)", cabin);

	Exit* forestAPathToHouse = new Exit("footprint path", "A path marked by human footprints", "Footprint path", "A path marked by human footprints", Exit::Direction::NORTH, forest, cabinOut);
	Exit* forestPathToCaveEntrance = new Exit("narrow path", "A narrow path between some rocks", "Narrow path", "A narrow path between some rocks", Exit::Direction::WEST, forest, caveEntranceRoom);
	Exit* caveEntrance = new Exit("cave hole", "A hole leading down", "Climbable stretch", "A hole leading upwards", Exit::Direction::DOWN, caveEntranceRoom, cave);
	Exit* cabinEntrance = new Exit("cabin door", "A door to the cabin", "Exit door", "A door towards the outside", Exit::Direction::NORTH, cabinOut, cabin);

	Creature * goblin = new Creature("Goblin", "An unusually large and terryfing goblin", cave, 10, 10, 5, 6, 0, 0);


	player = new Player("Sheldor", "You seem like a fine fella", forest, 25, 25, 5, 6, 2, 3);

	entities.push_back(cabin);
	entities.push_back(cabinOut);
	entities.push_back(caveEntranceRoom);
	entities.push_back(cave);
	entities.push_back(forest);
	entities.push_back(mailBox);
	entities.push_back(key);
	entities.push_back(box);
	entities.push_back(welcomeCard);
	entities.push_back(dagger);
	entities.push_back(rock);
	entities.push_back(forestAPathToHouse);
	entities.push_back(forestPathToCaveEntrance);
	entities.push_back(caveEntrance);
	entities.push_back(goblin);

	cout << "Welcome to a Zork homage by David Sierra! - Version 0.0.4\n";
}

World::~World() {
	//Iterate rooms and delete them
	vector<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.cend(); ++it) {
		if ((*it) != nullptr) {
			delete *it;
		}
	}
	delete player;
}

bool World::TryParseCommand(vector<string>& args) {

	bool res = true;

	switch (args.size()) {
	case 1: {//Plain commands

		if (CompareStrings(args[0], lookCmds)) {//LOOK
			player->Look();
		} else if (CompareStrings(args[0], clearCmds)) {//CLEAR CONSOLE
			system("CLS");
		} else if (CompareStrings(args[0], inventoryCmds)) { //CHECK INVENTORY
			player->CheckInventory();
		} else {
			res = false;
		}
		break;
	}
	case 2: {//"Command" + EntityName
		if (CompareStrings(args[0], lookCmds)) {		//LOOK

			if (!CompareStrings(args[1], selfCmds)) {
				Entity* lookTarget = player->GetRoom()->GetChildNamed(args[1].c_str());

				//Check Inventory
				if (lookTarget == nullptr) {
					lookTarget = player->GetChildNamed(args[1].c_str());
				}

				if (lookTarget != nullptr) {
					lookTarget->Look();
				} else {
					Println("No " + args[1] + " to be looked at");
				}
			} else {
				player->LookSelf();
			}
		} else if (CompareStrings(args[0], goCmds)) {		//GO
			const char * c = args[1].c_str();
			player->Go(c);
		} else if (CompareStrings(args[0], pickCmds)) {		//PICK
			player->Take(args);
		}

		else if (CompareStrings(args[0], equipCmds)) {		//EQUIP
			player->Equip(args);
		} else if (CompareStrings(args[0], unEquipCmds)) {	//UNEQUIP
			player->UnEquip(args);
		} else if (CompareStrings(args[0], examineCmds)) {	//EXAMINE
			if (!CompareStrings(args[1], selfCmds)) {
				Entity* targetToExamine = player->GetRoom()->GetChildNamed(args[1].c_str());
				if (targetToExamine == nullptr) {
					targetToExamine = player->GetChildNamed(args[1].c_str());
				}

				if (targetToExamine != nullptr) {
					if (targetToExamine->entityType == EntityType::CREATURE) {
						Creature* creatureToExamine = (Creature*)(targetToExamine);
						creatureToExamine->Inspect();
					} else if (targetToExamine->entityType == EntityType::ITEM) {
						Item* itemToExamine = (Item*)(targetToExamine);
						itemToExamine->Inspect();
					} else {
						Println("Can't examine " + targetToExamine->name);
					}
				}

			} else {
				player->Inspect();
			}
		} else if (CompareStrings(args[0], dropCmds)) {		//DROP
			player->Drop(args);
		} else {
			res = false;
		}
		break;
	}
	case 3: {
		if (CompareStrings(args[0], lookCmds)) {			//LOOK
			if (CompareStrings(args[1], lookPpsts)) {
				//To do Must call entities' Look() override if entity with name arg[2] is found (Only works with one of the correct prepositions)
				if (!CompareStrings(args[2], selfCmds)) {
					Entity* lookTarget = player->GetRoom()->GetChildNamed(args[2].c_str());
					if (lookTarget != nullptr) {
						lookTarget->Look();
					}
				} else {
					player->LookSelf();
				}
			}
		} else {
			res = false;
		}
		break;
	}
	case 4: {// "Command" + EntityName + "From" + EntityName

		if (CompareStrings(args[0], lookCmds)) {			//LOOK 
			Entity* eToLookAt = nullptr;
			eToLookAt = player->GetRoom()->GetChildNamed(args[3].c_str());
			if (eToLookAt != nullptr) {
				Entity* containerEntityToLookAt = nullptr;
				containerEntityToLookAt = eToLookAt->GetChildNamed(args[1].c_str());
				containerEntityToLookAt->Look();
			} else {
				Println("There's no " + args[3] + " here...");
			}
		} else if (CompareStrings(args[0], pickCmds)) {		// PICK
			player->Take(args);
		} else if (CompareStrings(args[0], unlockCmds)) {
			player->UnLock(args);
		} else if (CompareStrings(args[0], examineCmds)) {	//EXAMINE
			Entity* targetToExamineFrom = player->GetRoom()->GetChildNamed(args[3].c_str());

			if (targetToExamineFrom != nullptr) {
				Entity* targetToExamine = targetToExamineFrom->GetChildNamed(args[1].c_str());
				if (targetToExamine != nullptr) {
					if (targetToExamine->entityType == EntityType::CREATURE) {
						Creature* creatureToExamine = (Creature*)(targetToExamine);
						creatureToExamine->Inspect();
					} else if (targetToExamine->entityType == EntityType::ITEM) {
						Item* itemToExamine = (Item*)(targetToExamine);
						itemToExamine->Inspect();
					} else {
						Println("Can't examine " + targetToExamine->name);
					}
				} else {
					if (targetToExamineFrom->entityType == EntityType::CREATURE) {
						Println(targetToExamineFrom->name + " doesn't own " + args[3]);
					} else {
						Println("There's no " + args[3] + " insdie " + targetToExamineFrom->name);
					}
				}
			} else {
				Println("No " + args[3] + " to be found");
			}
		} else if (CompareStrings(args[0], dropCmds)) {		//DROP
			player->Drop(args);
		} else {
			res = false;
		}
		break;
	}
	default:
		res = false;
	}

	return res;
}
