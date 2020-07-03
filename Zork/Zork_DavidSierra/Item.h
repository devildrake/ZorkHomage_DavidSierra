#pragma once
#include "Entity.h"

class Item :Entity {
public:
	Item(const char* name, const char* desc, Entity* parent);
	~Item();
	void Look() const;

};