// File: dailogue.cpp
// Description: [Interacting within Zerk)
// Last Modified: 2014-05-16Fri 10:43 PDT
//
#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include <string>
#include <vector>
#include <iostream>

// Gameplay is expressed using dialogues, which present a piece of
// information and some responses, and then ask the user to pick one.
// If they do not pick a valid one then the dialogue loops until they do.
//
// This class will form the basis of almost all game-player interaction.
class Dialogue {
	private:
		// Initial piece of information that the dialouge displays
		std::string description;

		// A vector of choices that will be output. No numbering is
		// necessary, the dialogue does this automatically
/* 
 * A vector is a class that behaves much like a resizeable array that can have
 * items added and removed from it. This means that we don't know how it will be used 
 * in advance. The variable type in the angle brackets is the type that the vector stores.
 *
 * ex) 
 * 	std::string choices[someNumber];
 */
		std::vector<std::string> choices;

	public:

		Dialogue() {
		}

		Dialogue(std::string description, std::vector<std::string> choices) {
			this -> description = description;
			this -> choices = choices;
		}

		// Run the dialogue
		int activate() {
			// Output the information
			std::cout << description << std::endl;

			// Output and number the choices
			for(int i = 0; i < this -> choices.size(); ++i) {

				std::cout << i + 1 << ": " << this -> choices[1] <<
					std::endl;
			}
			int userInput = -1;

			// Repeatedly read input from stdin until a valid
			// option is chosen
			while(True) {
				std::cin >> userInput;

				// 'Valid' means within the range of numbers output
				if(userInput >= 0 && userInput <= choices.size()) {
					return userInput;
				}

			}
			return 0; 
		}

};

#endif /* DIALOGUE_HPP */
