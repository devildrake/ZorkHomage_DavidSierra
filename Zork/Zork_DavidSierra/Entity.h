#pragma once
#include <string>
#include <iostream>
#include <list>
#include "GlobalMethods.h"
using namespace std;

enum EntityType {
	ENTITY,
	ROOM,
	EXIT,
	CONTAINER,
	ITEM,
	CREATURE,
	NPC,
	PLAYER
};
class World;
//Base class from which all elements inherit some fields (name, description... as well as methods that all entitites must implement)
//All entities have a reference to the World instance and add themselves to the entities vector
class Entity {
public:
	EntityType entityType;
	std::string name;
	std::string description;
	World* world;
	Entity* parent;
	list<Entity*> entitiesContained;
	Entity(World* aWorld, const char* name, const char* description, Entity* parent);
	virtual ~Entity();
	virtual void Look() const;
	virtual void TakeAction();
	void SetNewParent(Entity*e);
	Entity* GetChildNamed(const char* targetName)const;
	vector<Entity*> GetChildrenOfType(EntityType type)const;
};
