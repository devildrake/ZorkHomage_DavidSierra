#pragma once
#include <vector>
#include "Player.h"
#include <stdlib.h>

using namespace std;
class Entity;
class Player;
class Creature;
class Exit;

class World {
public:
	vector<Entity*> entities;
	vector<Entity*> actingEntities;

	World();
	~World();
	bool gameFinished;
	bool TryParseCommand(vector<string>& args)const;
	bool CheckGameOver()const;
	Player* player;

};
