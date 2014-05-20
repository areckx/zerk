// File: creature.hpp
// Description: [Creature class for Zerk]
// Last Modified: 2014-05-16Fri 10:43 PDT
//
#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "inventory.hpp"
#include <string>
#include <iostream>

// We need at the very least a name and hit points, and three attributes:
// strength, dexterity, and vitality..
//
// Strength(str) will determine how much damage the player can do to other creatures.
// (we will use the same class for both players and creatures)
//
// Vitality(vit) will determine how many hit points(HP) they have.
//
// Dexterity(dex) will determine how fast and accurate they are.
//
// We should have a variable that determines hit rate(hitRate)
//
// We also need levels (lv) and experience(exp)
//
// We also need a class system (warrior, mage, etc) (className)

class Creature 
{

	public: 






		// Items that the creature posesses
		Inventory inventory;

		// Currently equipped weapon. Used as a pointer to an atlas entry,
		// but not necessary. nullptr denotes that no weapon is equipped
		Weapon* equippedWeapon;

		// Armor currently equipped in each slot
		Armor* equippedArmor[Armor::Slot::N];

		// Name of the creature and its class if it has one
		// Class may be Fighter, Rogue, Mage, etc
		// I will refer to the `class` as `vocation` outside of
		// the code to ease confusion
		std::string name;
		std::string className;

		// Create stats. Reasonable values are in parentheses
		int hp;		// Current HP (10~1000+)
		int maxHP;	// Maximum HP (10~1000+)
		int str;	// Strength determines damage in battle (1~100)
		int vit;	// Vitality determines  maximum HP (1~100)
		int dex;	// Dexterity determins speed in battle (1~100)
		double hitRate;	// Modifier to hit change (1~150)


		// Current level of the creature.
		// Determines the amount of exp that it gives to the
		// victor when defeated (see Battle class for more)
		// and the amount of exp required to level up again.
		// Upon leveling up the creature will gain stat improvements.
		// 1~50 is reasonable
		unsigned int level;

		// Current exp. 0~1M is reasonable, see the `levelUp()` function
		// for a decent scale.
		unsigned int exp;

		// Calculate the exp required to reach a certain level
		// *in total*
		unsigned int expToLevel(unsigned int level) 
		{

			// Exp tp level x = 128*x^2
			return 128 * level * level;
		}

		Creature(std::string name, int hp, int str, int vit,
				int dex, double hitRate, unsigned int level = 1,
				std::string className = "") 
		{

		// We also need to make sure that the creature is not equipped with
		// anything when they are first created 

			this->name = name;
			this->hp = hp;
			this->str = str;
			this->vit = vit;
			this->dex = dex;
			this->hitRate = hitRate;
			this->className = className;
			this->equippedArmor[Armor::Slot::HEAD] = nullptr;
			this->equippedArmor[Armor::Slot::TORSO] = nullptr;
			this->equippedArmor[Armor::Slot::LEGS] = nullptr;
			this->equippedWeapon = nullptr;
			this->level = level;
			this->exp = 0;
		}
		
		Creature()
		{ 
			this->equippedArmor[Armor::Slot::HEAD] = nullptr;
			this->equippedArmor[Armor::Slot::TORSO] = nullptr;
			this->equippedArmor[Armor::Slot::LEGS] = nullptr;
			this->equippedWeapon = nullptr;
			this->level = 1;
			this->exp = 0;
		}
	

		// Equip a weapon by setting the equipped weapon pointer. Currently
		// a pointless function(simple enough to be rewritten each time)
		// but handy if dual-wielding is ever added, or shields, etc.
		void equipWeapon(Weapon* weapon)
		{
			this->equippedWeapon = weapon;

			return;
		}

		// Equip the armor into its correct slot. A slightly more useful
		// function!
		void equipArmor(Armor* armor)
		{
			this->equippedArmor[(int)armor->slot] = armor;

			return;
		}


		// Level the creature to the next level if it has 
		// enough exp to do so, returning true if it could
		// level up and false otherwise.
		bool levelUp() 
		{

			// We want the exp to the next level,
			// not the current level
			if(this->exp >= expToLevel(this->level + 1)) 
			{

					// Advance to the next level
					++level;

					// Variables to keep track of stat changes. 
					// Neater than having a bunch of stat increases
					// all over the place, and removes the issue of 
					// the next level's stats affecting themselves
					// (increasing vit then increasing hp based on the 
					// boosted value instead of the original value,
					// for example:
					unsigned int hpBoost = 0;
					unsigned int strBoost = 0;
					unsigned int vitBoost = 0;
					unsigned int dexBoost = 0;

					// Give a large boost to hp every third level
					if(level % 3 == 0) 
					{

						// Randomly increase hp, but always give
						// a chunk proportional to the creature's
						// vit
						hpBoost = 10 + (rand() % 4) + this->vit / 4;
					}
					else 
					{
						// Just increase hp by a small amount
						hpBoost = this->vit / 4;
					}

					// If the creature is a Fighter, then favor str and vit
					// boosts over dex, but increase dex 50% of the time too
					if(this->className == "Fighter") 
					{

						strBoost = 1;
						vitBoost = 1;
						if(rand() % 2 == 0) dexBoost = 1;
					}
				
					// Same as Fighter but favor dex and vit instead. 
					// Rogues favor vit too in order to keep them roughly
					// the same capability
					if(this->className == "Rogue") 
					{

						vitBoost = 1;
						dexBoost = 1;
						if(rand() % 2 == 0) strBoost = 1;
					}

					// Adjust all of the variables accordingly
					this->maxHP += hpBoost;
					this->str += strBoost;
					this->vit += vitBoost;
					this->dex += dexBoost;

					// Tell the user that they grew a leve, what the
					// boosts were and what their stats are now

					std::cout << this->name << " grew to level" <<
						level << "!\n";
					std::cout << "HP +" << hpBoost << " -> " <<
						this->maxHP << std::endl;
					std::cout << "STR +" << strBoost << " -> " <<
						this->str << std::endl;
					std::cout << "VIT +" << vitBoost << " -> " <<
						this->vit << std::endl;
					std::cout << "DEX +" << dexBoost << " -> " <<
						this->dex << std::endl;
					std::cout << "--------------------\n";
					return true;
					}
			return false; 
		}


};
#endif  /* CREATURE_HPP */
