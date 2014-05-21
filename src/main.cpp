// File: main.cpp
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
#include "area.hpp"
#include "atlas.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "battle.hpp"



Creature dialogue_newchar();

void dialogue_menu(Creature& player);

int main(void) 
{
	// Atlas code
	std::vector<Creature> creatureAtlas;
	std::vector<Item> itemAtlas;
	std::vector<Weapon> weaponAtlas;
	std::vector<Armor> armorAtlas;
	std::vector<Area> areaAtlas;

	Creature player;

	// Build the atlases
	buildatlas_creature(creatureAtlas);
	buildatlas_item(itemAtlas);
	buildatlas_weapon(weaponAtlas);
	buildatlas_armor(armorAtlas);
	buildatlas_area(areaAtlas, itemAtlas, weaponAtlas,
			armorAtlas, creatureAtlas); 

	// Seed the random number generator with the system time, so the
	// random numbers produced by `rand()` will be different each time
	srand(time(NULL));

	// Main menu dialogue
	int result = Dialogue(
			"Welcome!",
			{"New Game"}).activate();

	switch(result) 
	{

		case 1: player = dialogue_newchar(); break;
		default: return 0; break;
	}

	// Set the current area to be the first area in the atlas,
	// essentially placing the character there upon game start.
	Area* currentArea = &(areaAtlas[0]);

	while(1) 
	{

		// If the player has died then inform them as such and
		// close the program.
		if(player.hp <= 0) 
		{
			std::cout << "\t----YOU DIED----\n	Game Over\n";
			return 0;
		}

		// If the area the player is in has any creatures inside it,
		// then begin a battle with the last creature in the list
		// before moving on to the next one. This makes the creature
		// list act like a stack
		if(currentArea->creatures.size() > 0)
		{
			for(int i = currentArea->creatures.size() - 1; i >= 0; --i)
				{
				Battle(&player, currentArea->creatures[i]).run();
				// Remove the creature from the area. This is fine 
				// to do because if the player wins the creature will
				// not respawn, and if the creature wins the player isn't
				// around to see it.(This does break the `non-mutable` 
				// feature of the atlases, but doing so saves a lot of
				// memory, as we don't need to keep two versions of the same
				// area.
				currentArea->creatures.pop_back();
				} 
		}




		// Activate the current area's dialogue
		result = currentArea->dialogue.activate();

		// These could be moved into the area code using an
		// event style system, but that allows for much less
		// flexibility with what happens in each area. Since
		// we're defining the areas in code anyway, sticking with
		// this isn't too much of a problem, and it keeps things easy
		// to understand.
		if(currentArea == &(areaAtlas[0]))
		{
			switch(result)
			{
				// Open the menu
				case 0:
					dialogue_menu(player);
					break;

				// Move to area 1
				case 1: 
					currentArea = &(areaAtlas[1]);
					break;

				// Search the area
				case 2: 
					currentArea->search(player);
					break;

				default:
					break;
			}
		}

		else if(currentArea == &(areaAtlas[1]))
		{
			switch(result)
			{
				// Open the menu
				case 0:
					dialogue_menu(player);
					break;
				// Move to area 0
				case 1:
					currentArea = &(areaAtlas[0]);
					break;

				// Search the area
				case 2:
					currentArea->search(player);
					break;

				default:
					break; 
			}
		} 
	}
	return 0;
}

// New character menu
//
// Generally returning an object from a function is not a good idea
// due to large memory footprints(returning is slow) but we're only 
// going to be calling this function once.
Creature dialogue_newchar() 
{
	
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

	switch(result) 
	{
		// Fighter class favors hp and str
		case 1:
			// Creature(name, hp, str, vit, dex, hitRate, level = 1, className="")
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

// Menu stuff
void dialogue_menu(Creature& player)
{
	// Output the menu
	int result = Dialogue(
		"Menu\n====",
		{"Items", "Equipment", "Character"}).activate();

	switch(result)
	{
		// Print the items that the player owns
		case 1:
			std::cout << "Items\n====\n";
			player.inventory.print();
			std::cout << "---------------\n";
			break;

		// Print the equipment that the player is wearing (If they
		// are wearing any equipment) and then ask if they want to
		// equip a weapon or some armor
		case 2:
		{


			std::cout << "Equipment\n==========\n";
			std::cout << "Head: "
				<< (player.equippedArmor[Armor::Slot::HEAD] != nullptr ?
				player.equippedArmor[Armor::Slot::HEAD]->name : "(empty)")
				<< std::endl;

			std::cout << "Torso: "
				<< (player.equippedArmor[Armor::Slot::TORSO] != nullptr ?
				player.equippedArmor[Armor::Slot::TORSO]->name : "(empty)")
				<< std::endl;

			std::cout << "Legs: "
				<< (player.equippedArmor[Armor::Slot::LEGS] != nullptr ?
				player.equippedArmor[Armor::Slot::LEGS]->name : "(empty)")
				<< std::endl;

			std::cout << "Weapon: "
				<< (player.equippedWeapon != nullptr ?
				player.equippedWeapon->name : "(empty)")
				<< std::endl;

			int result2 = Dialogue(
					"",
					{"Equip Armor", "Equip Weapon", "Close"}).activate();

			// Equipping armor
			if(result2 == 1)
			{
				int userInput = 0;

				// Can't equip armor if they do not have any.
				// Print a list of the armor and retrieve the
				// amount of armor in one go.
				int numItems = player.inventory.print_armor(true);
				if(numItems == 0) break;

				while(!userInput)
				{
					// Choose a piece of armor to equip
					std::cout << "Equip which item?\n";
					std::cin >> userInput;
					// Equipment is numbered but is stored
					// in a list, so the number must be converted
					// into a list element.
					if(userInput >= 1 && userInput <= numItems)
					{
						int i = 1;

						for(auto it : player.inventory.armor)
						{
							if(i++ == userInput)
							{
								// Equip the armor if
								// it is found
								player.equipArmor(it.first);
								break;
							}
						}
					}
				}
			}
		

			// Equip a weapon, using the same algorithms as for armor
			else if(result2 == 2)
			{
				int userInput = 0;
				int numItems = player.inventory.print_weapons(true);

				if(numItems == 0) break;

				while(!userInput)
				{
					std::cout << "Equip which item?\n";
					std::cin >> userInput;
					if(userInput >= 1 && userInput <= numItems)
					{
						int i = 1;

						for(auto it : player.inventory.weapons)
						{
							if(i++ == userInput)
							{
								player.equipWeapon(it.first);
								break;
							}
						}
					}
				}
			} 
			std::cout << "---------------\n";
			break;
		
		}
		// Output the character information
		
		case 3: 
			std::cout << "Character\n==========\n";
			std::cout << player.name;

			if(player.className != "") std::cout << " the " << player.className;
			std::cout << std::endl;

			std::cout << "HP: " << player.hp << " ／ " << player.maxHP << std::endl;
			std::cout << "STR: " << player.str << std::endl;
			std::cout << "VIT: " << player.vit << std::endl;
			std::cout << "DEX: " << player.dex << std::endl;
			std::cout << "Lv: " << player.level << " (" << player.exp;
			std::cout << "　／ " << player.expToLevel(player.level+1) << ")\n";
			std::cout << "---------------\n";
			break;

		default:
			break;

	}
	return;
}
	 
	//EOF
