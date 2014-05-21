// File: battle.hpp
// Description: [Battle class for Zerk]
// Last Modified: 2014-05-16Fri 10:43 PDT
//
#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "dialogue.hpp"
#include "creature.hpp"
#include "armor.hpp"
#include "weapon.hpp"

#include <iostream>

class Battle
{

	public:

		// Dialogue used to ask player battle choices
		Dialogue dialogue;

		// Creatures in combat. creatures[0] is the player
		Creature* creatures[2];

		Battle()
		{
		}

		Battle(Creature* player, Creature* b)
		{
			// Start a battle with the player and another creature
			this->creatures[0] = player;
			this->creatures[1] = b;

			// Set up the dialogue. Defending offers no tactical
			// advantage in this battle system
			this->dialogue = Dialogue("What will you do?",
					{
					"Attack", 
					"Defend"
					}); 
		}

		// Creature a attacks creature b, and b takes damage accordingly
		void attack(Creature* a, Creature* b)
		{
			std::cout << a->name << " attacks!\n";

			// Damage that a will inflict on b
			int damage = 0;

			// Cumulative modifier to hitRate
			double hitRate = a->hitRate;

			// If a has equipped a weapon, then add the weapon damage
			// on to the current damage and add the hitRate on to the 
			// current hitRate
			if(a->equippedWeapon != nullptr)
			{
				damage += a->equippedWeapon->damage;
				hitRate += a->equippedWeapon->hitRate;
			}

			// Increase the damage by half the attacker's strength
			damage += a->str / 2;
			
			// Damage that b will block
			int defense = 0;

			// Sum the defense values of the armor that b has equipped, 
			// and increase the defense by the summed value
			for(int i = 0; i < Armor::Slot::N; ++i)
			{
				if(b->equippedArmor[i] != nullptr)
					defense += b->equippedArmor[i]->defense;
			}

			// Decrease the damage by the damage blocked, then ensure that
			// damage is always inflicted (we don't want battles to last 
			// forever, nor do we want attacks to heal the wounded!)
			damage -= defense;
			if(damage < 1) damage = 1;

			// Add the hitRate to the base hitRate and subtract the
			// target's dex from it. Instead of halving it to normalize
			// it into a percentage, we just double the angle of randomly
			// generated values
			if(rand() % 201  <= 170 + hitRate - b->dex)
			{
				// The attack hit, so subtract damage
				std::cout << b->name << " takes " << damage << " damage!\n";
				b->hp -= damage;
			}
			else
			{
				// The attack missed
				std::cout << a->name << " missed!\n";
			}
			return;
		}

		// Allow the player to act
		void playerTurn()
		{
			// Activate the dialogue and allow the player to 
			// choose their battle option
			int result = this->dialogue.activate();

			switch(result)
			{
				// Attack the enemy
				case 1:
					attack(creatures[0], creatures[1]);
					break;

				// Defend, skipping to the enemy's turn
				case 2:
					std::cout << creatures[0]->name << " defends.\n";
					break;

				default:
					break;
			}
			return;
		}

		// Allow the enemy to attack
		void enemyTurn()
		{
			// Battle system does not currently allow for any kind
			// of tactics, so make the enemy attack blindly
			attack(creatures[1], creatures[0]);

			return;
		}

		// Return true if the creature is dead. Split into its own function
		// to allow easy addition of effects which simulate death, such as
		// petrification or banishment. 
		bool isDead(Creature* creature)
		{
			if(creature->hp <= 0)
			{
				return true;
			}
			return false;
		}

		// Run a round of the battle
		bool activate()
		{
			// The creature with the highest dex attacks first,
			// with preference to the player
			if(creatures[0]->dex >= creatures[1]->dex)
			{
				// Run each turn and check if the foe is dead at
				// the end of each
				this->playerTurn();
				if(isDead(creatures[1]))
				{
					std::cout << creatures[1]->name 
						<< " was defeated!\n";
					return true;
				}
				this->enemyTurn();
				if(isDead(creatures[0]))
				{
					std::cout << creatures[0]->name
						<< " was defeated!\n";
					return true;
				}
			}
			else 
			{
				this->enemyTurn();
				if(isDead(creatures[0]))
				{
					std::cout << creatures[0]->name 
						<< " was defeated!\n";
				return true;
				}

				this->playerTurn();
				if(isDead(creatures[1]))
				{
					std::cout << creatures[1]->name
						<< " was defeated!\n";
					return true;
				}
			}
			return false;
		}

		// Begin the battle
		void run()
		{
			std::cout << creatures[1]->name << " appears!\n";

			// Run the battle until one creature dies
			while(!this->activate());

			// If the enemy is dead, then allocate exp to
			// the player
			if(isDead(creatures[1]))
			{
				// Give exp to the player equal to 1/8
				// the exp the enemy gained to reach its
				// next level
				unsigned int expGain =
					creatures[1]->expToLevel(creatures[1]->level+1) / 8;
				std::cout << "Gained " << expGain << " exp!\n";
				creatures[0]->exp += expGain;

				// Repeatedly level up the player until they are the 
				// highest level they can be for their exp
				while(creatures[0]->levelUp()); 
			}
			return; 
		}
}; 

#endif /* BATTLE_HPP */ 
//EOF
