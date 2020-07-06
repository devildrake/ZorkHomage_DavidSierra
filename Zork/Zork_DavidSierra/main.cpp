#include <iostream>
#include <string>
#include <vector>
#include "GlobalMethods.h"
#include "World.h"
#include "Room.h"

using namespace std;

//Strings used to check for exit input
const string exitStrings[5] = { "exit","quit","close","salir","cerrar" };

int main()
{
	char player_input[100];
	vector<string>commandArguments;

	World aWorld;

	while (1) {
		cout << "-";
		cin.getline(player_input, sizeof(player_input));
		TranslateToArguments(player_input, commandArguments);

		if (commandArguments.size() > 0) {
			string auxString = "";

			for (size_t i = 0; i < commandArguments.size(); i++) {
				auxString += commandArguments[i];
				auxString += " ";
			}

			if (!aWorld.TryParseCommand(commandArguments)) {
				if (CompareStrings(player_input, exitStrings)) {
					cout << "Thanks for playing! Bye!\n";
					break;
				}
				else {
					cout << "Command not found\n";
				}
			}
			commandArguments.clear();
		}

	}
	return 1;
}
