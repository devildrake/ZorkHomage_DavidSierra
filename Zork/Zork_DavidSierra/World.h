#pragma once
#include <vector>
#include <stdlib.h>

using namespace std;
class Entity;
class Player;
class Creature;
class Exit;

class World {
public:
	vector<Entity*> entities;
	vector<Creature*> creatures;
	World();
	~World();

	bool TryParseCommand(vector<string>& args)const;
private:
	Player* player;

};