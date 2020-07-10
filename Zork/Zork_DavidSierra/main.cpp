#include <iostream>
#include <string>
#include <vector>
#include "GlobalMethods.h"
#include "World.h"
#include "Room.h"
#include <time.h>

using namespace std;

//Strings used to check for exit input
const string exitStrings[5] = { "exit","quit","close","salir","cerrar" };

int main() {
	char player_input[100];
	vector<string>commandArguments;
	srand((unsigned int)time(NULL));

	bool gameOver = false;
	World aWorld;

	while (!gameOver) {
		cout << "-";
		cin.getline(player_input, sizeof(player_input));
		TranslateToArguments(player_input, commandArguments);

		if (commandArguments.size() > 0) {
			string auxString = "";

			for (size_t i = 0; i < commandArguments.size(); i++) {
				auxString += commandArguments[i];
				auxString += " ";
			}
			if (CompareStrings(player_input, exitStrings)) {
				break;
			} else {
				if (!aWorld.TryParseCommand(commandArguments)) {
					Println("Command not found");
				}
				gameOver = aWorld.CheckGameOver();
				if (gameOver) {
					Println("Game Over!");
				}
			}
			commandArguments.clear();

		}

	}

	Println("===================");
	Println("===================");
	Println("Thanks for playing!");
	Println("===================");
	Println("===================");
	system("pause");
	return 1;
}
