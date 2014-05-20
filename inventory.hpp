// File: inventory.hpp
// Description: [Inventory class for Zerk]
// Last Modified: 2014-05-16Fri 10:43 PDT
//
#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"
#include "weapon.hpp"
#include "armor.hpp"

#include <list>
#include <utility>
#include <iostream>

class Inventory {
	
	public:
		// Whilst weapons and armor are also items, they have their own 
		// specific properties, and so cannot be stored inside the same
		// list as the items. We use a list and not a vector as inventories
		// are highly mutable. This way they can also be efficiently sorted.
		// The first element of the pair stores a pointer to the item in the
		// item/weapon/armor atlas, defined as main(), and the second element
		// stores the quantity of the item.
		std::list<std::pair<Item*, int>> items;
		std::list<std::pair<Weapon*, int>> weapons;
		std::list<std::pair<Armor*, int>> armor;


		Inventory() {

		}

		Inventory(std::list<std::pair<Item*, int>> items,
				std::list<std::pair<Weapon*, int>> weapons,
				std::list<std::pair<Armor*, int>> armor) {

			this->items = items;
			this->weapons = weapons;
			this->armor = armor; 
		} 
};


#endif /* INVENTORY_HPP */
