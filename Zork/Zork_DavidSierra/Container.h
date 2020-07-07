#pragma once
#include "Entity.h"
class Container : public Entity {
public:
	Entity* keyToUnlock;
	bool isLocked;
	bool pickeable;
	Container(const char* name, const char* desc, Entity* parent, Entity* keyToUnlock = nullptr);
	~Container();
	void Look() const;

};