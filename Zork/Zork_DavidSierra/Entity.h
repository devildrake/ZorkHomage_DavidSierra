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

//Base class from which all elements inherit some fields (name, description... as well as methods that all entitites must implement)
class Entity {
public:
	EntityType type;
	std::string name;
	std::string description;

	Entity* parent;
	list<Entity*> entitiesContained;
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();
	virtual void Look() const;

	void SetNewParent(Entity*e);
	Entity* GetChildNamed(const char* targetName)const;
};
