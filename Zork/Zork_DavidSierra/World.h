#pragma once
#include <vector>

using namespace std;
class Entity;
class Player;
class Room;

class World
{
public:

	World();
	~World();

	bool TryParseCommand(vector<string>& args);

private:
	vector<Room*> rooms;
	vector<Entity*> entities;
	Player* player;
};