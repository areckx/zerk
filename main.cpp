// File: maincpp
// Description: [Zerk Main]
// Last Modified: 2014-05-16Fri 10:43 PDT
//

// we are developing this game using the standard C++ i/o stream, and will require
// at least a random number generator1 and string, vector, and list classes
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include <ctime>

#include "dialogue.hpp"
#include "creature.hpp"

// New character menu
//
// Generally returning an object from a function is not a good idea
// due to large memory footprints(returning is slow) but we're only 
// going to be calling this function once.
Creature dialogue_newchar() {
	
	// Ask for name and class 
	// Name does not use a dialogue since dialogues only
	// request options, not string input. Could be generalized
	// into its own TextInput class, but not necessary
	std::cout << "Choose your name" << std::endl;
	std::string name;
	std::cin >> name;

	int result = Dialogue(
			"Choose your class",
			{"Fighter", "Rogue"}).activate();
		/* // C++03 requires vectors //
		 *
		 * std::vector<std::string> > choices;
		 * choices.push_back("Fighter");
		 * choices.push_back("Rogue");
		 * int result = Dialogue("Choose your class", choices).activate();
		 */

	switch(result) {
		// Fighter class favors hp and str
		case 1:
			return Creature(name, 35, 20, 10, 5, 10.0, 1,
					"Fighter");
			break;

		// Rogue class favors dex and hitRate
		case 2:
			return Creature(name, 30, 5, 10, 20, 15.0, 1,
					"Rogue");
			break;

		// Default case that should never happen, but good to be safe
		default:
			return Creature(name, 30, 10, 10, 10, 10.0, 1,
					"Adventurer");
			break;
	}

}

int main(void) {
	Creature player;

	// Seed the random number generator with the system time, so the
	// random numbers produced by `rand()` will be different each time
	srand(time(NULL));

	// Main menu dialogue
	int result = Dialogue(
			"Welcome!",
			{"New Game"}).activate();

	switch(result) {

		case 1: player = dialogue_newchar(); break;
		default: return 0; break;
	}

	while(1) {

		// If the player has died then inform them as such and
		// close the program.
		if(player.hp <= 0) {
			std::cout << "\t----YOU DIED----\n	Game Over\n";
			return 0;
		}

	}
	return 0;
}

// TODO 
// 	[+] Make some classes
