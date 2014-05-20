// File: zerk.cpp
// Description: [A text-based RPG]
// Last Modified: 2014-05-16Fri 10:43 PDT
//
#include <iostream>
#include <cstdlib>


// This game should be able to ::
// 	[] Lead the player to various locations
//
// 	[] Allow the player to inspect things
//
// 	[] Allow the player to hold and use items such as keys, weapons, food, etc.
//
// 	[] Display the player's current health status, including ::
// 		
// 		* Health points
// 		* Hunger level
//		* Energy level 
//
//	[] Use a time-tracking system to simulate the passing of time, day/night.
//		
//		* There are different challenges at night
//
//		* Some tasks can only be completed at either day/night
//
// 	[] Allow the player to save his/her progress
//
// 	[] Present challenging enemies such as ogres to battle
//
// 	[] Allow the player to interact with friendly characters, some of whome
// 	   may aid the player on his/her journey
//

/*					   :: Basic Story Line ::
 *
 * You have woken up inside of some sort of laboratory. How you got here, you can't remember. There is a
 * sharp pain in your left shoulder. You hear whispering from across the room. You yell out in pain and they
 * come toward you. 
 *
 *
 * 	[] The Escape
 *
 */
int main() 
{
	int health = 100;
	int stamina = 100;
	int hunger = 0;
	int menu = 0;
	int items = [];

	while (health > 0) 
	{

		std::cout << "\t\tWelcome to Zerk!" << std:endl <<
			std::endl; << "\t\t--==Main Menu==--" << std::endl <<
			"[1] ::New Game::" << std::endl << "[2] ::Continue::" <<
			std::endl << "[3] Quit" << std::endl;

		std::cin >> menu;

		if (menu == 1) 
		{

		}

		if (menu == 2) 
		{

		}

		if (menu == 3) 
		{ 
			std::exit();
		
		}


	}


}




/*
 * 	[] Into the mountains
 *
 * 	[] Danger approaches
 *
 * 	[] The plot thickens...
 *
 * 	[] Deeper into the mountain lies the truth
 *
 * 	[] Betrayal!
 *
 * 	[] Back to the lab?
 *
 * 	[] It all makes sense now
 *
 * 	[] Self Destruct!
 *
 * 	[] Final Countdown
 *
 * 	[] Back to the mountains and beyond
 *
 * 	[] The lab was only the beginning!
 *
 * 	[] Gateway into another realm
 *
 * 	[] Your true power awakens
 *
 * 	[] Allies
 *
 * 	[] Find the killer
 *
 * 	[] Main Headquarters
 *
 * 	[] Deeper and deeper, more mysteries
 *
 * 	[] Solve the puzzles
 *
 * 	[] Find the key
 *
 * 	[] Now you know what you must do...
 *
 * 	[] Final Stretch
 *
 * 	[] The end
 */
