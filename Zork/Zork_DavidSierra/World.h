#pragma once
#include <vector>
#include <stdlib.h>

using namespace std;
class Entity;
class Player;
class Room;
class Exit;

class World
{
public:

	World();
	~World();

	bool TryParseCommand(vector<string>& args);

private:
	vector<Room*> rooms;
	vector<Exit*> exits;
	vector<Entity*> entities;
	Player* player;
};