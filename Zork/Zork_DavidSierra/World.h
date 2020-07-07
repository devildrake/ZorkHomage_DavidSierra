#pragma once
#include <vector>
#include <stdlib.h>

using namespace std;
class Entity;
class Player;
class Exit;

class World {
public:
	vector<Entity*> entities;
	World();
	~World();

	bool TryParseCommand(vector<string>& args);
private:
	Player* player;

};