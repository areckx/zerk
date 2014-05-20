// File: armor.cpp
// Description: [Armor class for Zerk]
// Last Modified: 2014-05-16Fri 10:43 PDT
//
#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "item.hpp"

#include <string>

// Armor should also inherit Item properties
class Armor : public Item {

	public:
		// Armor can go into one of three slots1, and only one piece of
		// armor may occupy each slot at a time. The N is there to quickly
		// retrieve the number of slots, without having to use another variable.
		enum Slot { TORSO, HEAD, LEGS, N }; // Gloves don't go on HEAD, etc

		Slot slot;

		// See Battle class for exact formula, values from 1~50 are
		// reasonable.
		int defense;

		// Usual constructor
		Armor(std::string name, std::string description, int defense,
				Armor::Slot slot) : 
				Item(name, description) {

			this->defense = defense;
			this->slot = slot;

		}

		Armor() {

		}
		

};


#endif /* ARMOR_HPP */
