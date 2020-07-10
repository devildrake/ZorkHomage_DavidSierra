#include "World.h"
#include <iostream>
#include "GlobalMethods.h"
#include "Equipable.h"
#include "Container.h"
#include "Exit.h"
#include "Room.h"
#include "Player.h"
#include "Cart.h"
#include "ScaredChild.h"
#include "HealthPotion.h"

//Hardcoded keys that are later to compare and parses commands
const string lookCmds[3] = { "look","l" };
const string lookPpsts[3] = { "at","to" };
const string goCmds[3] = { "go","walk","move" };
const string selfCmds[3] = { "me","self","myself" };
const string clearCmds[4] = { "clear","wipe","clr","cls" };
const string pickCmds[4] = { "pick","grab","take","get" };
const string inventoryCmds[3] = { "inventory", "inv","i" };
const string unlockCmds[2] = { "open", "unlock" };
const string equipCmds[2] = { "equip","eq" };
const string unEquipCmds[2] = { "unequip","uneq" };
const string examineCmds[4] = { "examine","ex","inspect","ins" };
const string dropCmds[2] = { "drop", "place" };
const string atkCmds[3] = { "strike","attack","kill" };
const string consumeCmds[3] = { "use","consume","drink" };

World::World() {
	//Farm
	Room* farmHouse = new Room(this, "Farm house", "A small house, there's tools and furniture all over the place");
	Room* farmAttic = new Room(this, "Farm attic", "A dim light enters from between the planks and iluminates an attic with a few haystacks");
	Room* farmEntrance = new Room(this, "Farm entrance", "The only entrance to an apparently deserted farm");
	Room* farmStables = new Room(this, "Farm stables", "The farm's stables, there's blood pools where horses should be, as well as trails leading to holes in the walls going outside");
	Room* farmOut = new Room(this, "Outside of farm", "The entrance of a small farm");

	//Forest
	Room* forestOutSkirts = new Room(this, "Forest outskirts", "An entrance to the forest");
	Room* forest = new Room(this, "Forest", "A beautiful forest that seems neverending");


	Room* caveEntrance = new Room(this, "Cave Entrance", "A hole in the ground appears to lead toward a cave");
	Room* cave = new Room(this, "Cave ", "A small cave lit by small holes on the walls");
	Room* clearing = new Room(this, "Clearing", "A clearing");
	Room* woodsmanCabin = new Room(this, "Woodsman cabin", "An old cabin full of dust and rusty tools");
	Room* lake = new Room(this, "Lake", "A big lake");


	Exit* farmOutToFarmEntrance = new Exit(this, "simple road", "marked by wheels", "simple road", "marked by wheels", Exit::Direction::EAST, farmOut, farmEntrance);
	Exit* farmEntranceToFarmHouse = new Exit(this, "broken door", "with bloodstains", "broken door", "with bloodstains", Exit::Direction::NORTH, farmEntrance, farmHouse);
	Exit* farmEntranceToFarmStables = new Exit(this, "double door", "with burning marks and partially scortched", "double door", "with burning marks and partially scortched", Exit::Direction::EAST, farmEntrance, farmStables);
	Exit* farmOutToForestOutskirts = new Exit(this, "road", "severly marked by wheels", "road", "severly marked by wheels", Exit::Direction::SOUTH, farmOut, forestOutSkirts);
	Exit* forestOutskirtsToForest = new Exit(this, "path", "", "path", "", Exit::Direction::SOUTH, forestOutSkirts, forest);
	Exit* forestOutskirtsToCaveEntrance = new Exit(this, "path", "which is partially hidden", "path", "", Exit::Direction::WEST, forestOutSkirts, caveEntrance);
	Exit* caveEntranceToFarmOutskirts = new Exit(this, "path", "", "path", "", Exit::Direction::NORTH, caveEntrance, farmOut, true);
	Exit* caveEntranceToForest = new Exit(this, "path", "", "climbable stretch", "hole leading upwards", Exit::Direction::SOUTH, caveEntrance, forest, true);
	Exit* forestToClearing = new Exit(this, "path", "", "path", "", Exit::Direction::EAST, forest, clearing);
	Exit* clearingToForestOutskirts = new Exit(this, "path", "", "path", "", Exit::Direction::NORTH, clearing, forestOutSkirts, true);
	Exit* clearingToLake = new Exit(this, "path", "", "path", "", Exit::Direction::EAST, clearing, lake);
	Exit* clearingToWoodsmanCabin = new Exit(this, "empty doorway", "", "empty doorway", "", Exit::Direction::SOUTH, clearing, woodsmanCabin);
	Exit* lakeToForestOutskirts = new Exit(this, "path", "", "path", "", Exit::Direction::NORTH, lake, forestOutSkirts, true);
	Exit* cabinToLake = new Exit(this, "window", "", "", "", Exit::Direction::EAST, woodsmanCabin, lake, true);

	Container* chest = new Container(this, "Chest", "A small chest", woodsmanCabin);
	Entity* key = new Entity(this, "Key", "A small key with a horse sigil carved", chest);
	Exit* farmHouseToFarmBasement = new Exit(this, "trapdoor", "", "trapdoor", "", Exit::Direction::UP, farmHouse, farmAttic, false, key);
	Entity* doll = new Entity(this, "doll", "a raggedy doll that must belong to some kid", farmStables);
	ScaredChild*child = new ScaredChild(this, "child", "a trembling child", "hands", farmAttic, 5, 5, 0, 0, 0, 0, 50, 0, doll, nullptr, farmOut, "The child is quietly playing with her doll in the cart");
	Entity* chisel = new Entity(this, "chisel", "a magic chisel with goblin markings", child);
	Exit* caveEntranceToCave = new Exit(this, "hole", "leading down", "climbable stretch", "with a hole leading upwards", Exit::Direction::DOWN, caveEntrance, cave, false, chisel);

	child->itemToDrop = chisel;

	Entity* woodsManNote = new Entity(this, "Note", "The note reads: Lovegood me old pal, I left an extra copy of the trapdoor I made for yer house in my cabin south of the clearing just in case you lost yours, since your kid is always playing with it, stay safe friend! I sure will once I'm away from here!", farmHouse);

	Container* mailBox = new Container(this, "Mailbox", "A rusty mailbox", farmOut);
	Entity* welcomeLetter = new Entity(this, "Letter", "The letter reads: \nDear Mr Lovegood,\nYour request for an adventurer for the apparent presence of goblins in your area has been notified to the guild and the payment has been accepted, Please stand by and try to stay safe until an adventurer arrives.\nSigned Adventurer Guild administration.", (Entity*)mailBox);

	//Goblin
	Creature* goblin = new Creature(this, "Goblin", "An unusually large and terryfing goblin", "claws", cave, 10, 10, 2, 5, 0, 0, 5, 20);
	Equipable* armour = new Equipable(this, "Armour", " A light armour with goblin symbols around it, it should make a fine proof of mission complete, you should place it in your cart", goblin, ItemType::ARMOUR, pair<int, int>{0, 0}, pair<int, int>{3, 4});
	goblin->Equip(armour);

	//Slime
	Creature* slime = new Creature(this, "Slime", "A harmless slime", "body", lake, 10, 10, 3, 4, 0, 0, 5, 20);
	Equipable* axe = new Equipable(this, "Axe", "A rusty old axe", slime, ItemType::WEAPON, pair<int, int>{4, 6}, pair<int, int>{2, 3});
	HealthPotion* potion = new HealthPotion(this, "Potion", "A healing potion", slime, 15);

	Cart* cart = new Cart(this, "Cart", "Your trusted old cart, pulled by your horse alone", farmOut, armour);
	Entity* rock = new Entity(this, "Rock", "An engraved rock that reads: property of Tanya, it has a hole in the shape of a key underneath it, but it's empty", farmHouse);
	Creature* deadFarmer = new Creature(this, "Farmer", "A bloody farmer with multiple claw wounds", "Fists", farmStables, 10, 0, 0, 0, 0, 0, 0, 0);

	Entity* sign = new Entity(this, "Sign", "A sign that reads points in directions\n ->To the north: Lovegood Farm\n ->To the south: Woodsman cabin (ABANDONED)", clearing);
	player = new Player(this, "Sheldor", "You and your lonely self", "fists", farmOut, 15, 15, 3, 5, 0, 2, 20, 10);
	Equipable* dagger = new Equipable(this, "Dagger", "A small rusty dagger", (Entity*)player, ItemType::WEAPON, pair<int, int>{1, 4}, pair<int, int>{1, 2});

	Entity* picture = new Entity(this, "Picture", "A drawing of the farm you live in, on the backside it reads:\n-My stubborn brother, please remember to read this whenever you go out on adventures, remember to be careful cause you've got a home to come back to! And don't forget to equip your dagger! Love, Mia", cart);

	//Creatures added to creatures vector will have the ability to "act" after each command the player inputs
	actingEntities.push_back(goblin);
	actingEntities.push_back(child);
	actingEntities.push_back(cart);
	actingEntities.push_back(slime);
	cout << "Welcome to a Zork homage by David Sierra! - Version 0.0.6\n";
}

World::~World() {
	//Iterate entities and delete them
	vector<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.cend(); ++it) {
		if ((*it) != nullptr) {
			delete *it;
		}
	}
	entities.clear();
	actingEntities.clear();
}

bool World::CheckGameOver()const {
	return !player->IsAlive() || gameFinished;
}

bool World::TryParseCommand(vector<string>& args)const {

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
		} else if (CompareStrings(args[0], equipCmds)) {		//EQUIP
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
		} else if (CompareStrings(args[0], atkCmds)) {		//DROP
			if (!CompareStrings(args[1], selfCmds)) {
				player->Attack(args);
			} else {
				Println(player->name + " commits Harakiri");
				player->health = 0;
				Println(player->name + " died!");
			}
		} else if (CompareStrings(args[0], consumeCmds)) {
			player->Consume(args);
		} else {
			res = false;
		}
		break;
	}
	case 3: {// Some commands that can admit prepositions
		if (CompareStrings(args[0], lookCmds)) {			//LOOK
			if (CompareStrings(args[1], lookPpsts)) {
				if (!CompareStrings(args[2], selfCmds)) {
					Entity* lookTarget = player->GetRoom()->GetChildNamed(args[2].c_str());

					if (lookTarget == nullptr) {
						lookTarget = player->GetChildNamed(args[2].c_str());
					}

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
	for (vector<Entity*>::const_iterator it = actingEntities.begin(); it != actingEntities.cend(); ++it) {
		(*it)->TakeAction();
	}

	if (gameFinished) {
		Println("==================================");
		Println(player->name + " hops into his carriage with his mission complete, and while he's on his way to collect his reward, he notices the little girl hiding between his bearings, he's just gained a new friend");
		Println("To be continued...");
	}

	return res;
}

