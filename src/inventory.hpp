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

class Inventory 
{
	
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


		Inventory() 
		{

		}

		Inventory(std::list<std::pair<Item*, int>> items,
				std::list<std::pair<Weapon*, int>> weapons,
				std::list<std::pair<Armor*, int>> armor) 
		{

			this->items = items;
			this->weapons = weapons;
			this->armor = armor; 
		} 

		// Add an item to the inventory, specified by a pointer to it
		// from the item atlas(technically doesn't need to point there,
		// but it should anyway.)
		void add_item(Item* item, int count)
		{ 
			// Increase the quantity of the item if it already exists
			for(auto& it : this->items) 
			{

				if(it.first == item) 
				{
					it.second += count; 
				return;
				}
			} 
			// If the item doesn't already exist in the inventory, then
			// a pair must be created too
			this->items.push_back(std::make_pair(item, count)); 
		}

		// Same as `add_item()` but for weapons
		void add_weapon(Weapon* weapon, int count) 
		{ 
			for(auto& it : this->weapons) 
			{

				if(it.first == weapon) 
				{
					it.second += count; 
					return;
				}
			}
			this->weapons.push_back(std::make_pair(weapon, count)); 
		}

		// Same but for armor
		void add_armor(Armor* armor, int count) 
		{

			for(auto& it : this->armor) 
			{ 
				if(it.first == armor) 
				{ 
					it.second += count; 
					return;
				} 
			}
			this->armor.push_back(std::make_pair(armor, count)); 
		}

		// Remove the specified number of items from the inventory
		void remove_item(Item* item, int count)
		{ 
			// Iterate through the items, and if they are found then
			// decrease the quantity by the quantity removed
			for(auto& it : this->items) 
			{
				if(it.first == item)
				{
					it.second -= count;
				}
			// Iterate through the list again, and remove any elements 
			// from the list that have zero or less in their quantity.
			// We do this in two passes because removing an element from
			// a list during a for loop invalidates the iterators, and 
			// the loop stops working.
			this->items.remove_if([](std::pair<Item*, int>& element)
			{ // lambda function
			  // **function that doesn't exist by itself but are
			  // defined in the place that they are called**
				return element.second < 1;
			});
			}
		}
		// Same for weapons
		void remove_weapon(Weapon* weapon, int count)
		{
			for(auto& it : this->weapons)
			{
				if(it.first == weapon)
				{
					it.second -= count;
				}
			this->weapons.remove_if([](std::pair<Weapon*, int>& element)
			{
				return element.second < 1;
			});
			}
		}

		// Same for armor
		void remove_armor(Armor* armor, int count)
		{
			for(auto& it : this->armor)
			{
				if(it.first == armor)
				{
					it.second -= count;
				}
			this->armor.remove_if([](std::pair<Armor*, int>& element)
			{
				return element.second < 1; 
			});
			}
		}


		// Merge the specified inventory with the current one, adding
		// item quantities together if they already exist and adding the 
		// item into a new slot if they do not.
		void merge(Inventory* inventory)
		{
			// You can't merge an inventory with itself!
			if(inventory == this) return;

			// Loop through the items to be added, and add them. Our
			// addition function will take care of everything for us.
			for(auto it : inventory->items)
			{
				this->add_item(it.first, it.second);
			}

			// Do the same for the weapons.
			for(auto it : inventory->weapons)
			{
				this->add_weapon(it.first, it.second);
			}
			// Do the same for the armor
			for(auto it : inventory->armor)
			{
				this->add_armor(it.first, it.second);
			}
			return;
		} 


		// Destroy all items in the inventory (they remain in the atlas, though)
		void clear()
		{
			this->items.clear();
			this->weapons.clear();
			this->armor.clear();
		}


		// Output a list of the items into stdout, formatted nicely 
		// and numbered if required
		int print_items(bool label = false)
		{
			unsigned int i = 1;

			for(auto it : this->items)
			{
				// Number the items if asked
				if(label) std::cout << i++ << ": ";
				// Outpit the item name, quantity, and description
				// e.g. Gold Piece (29) - Glimmering disks of wealth
				std::cout << it.first->name << " (" << it.second << ") - ";
				std::cout << it.first->description << std::endl;
			}

			// Return the number of items output, for convenience
			return this->items.size();
		}

		// Same for weapons
		int print_weapons(bool label = false)
		{
			unsigned int i = 1;

			for(auto it : this->weapons)
			{
				if(label) std::cout << i++ << ": ";
				std::cout << it.first->name << " (" << it.second << ") - ";
				std::cout << it.first->description << std::endl;
			}
			return this->weapons.size();
		}

		// Same for armor
		int print_armor(bool label = false)
		{
			unsigned int i = 1;

			for(auto it : this->armor)
			{
				if(label) std::cout << i++ << ": ";
				std::cout << it.first->name << " (" << it.second << ") - ";
				std::cout<< it.first->description << std::endl;
			}
			return this->armor.size();
		}

		// Print the entire inventory: items, weapons, armor,
		// but if nothing in the inventory, print "(empty)"
		void print(bool label = false)
		{
			if(this->items.size() == 0 &&
					this->weapons.size() == 0 &&
					this->armor.size() == 0)
			{
				std::cout << "(empty)" << std::endl;
			}
			else
			{
				this->print_items(label);
				this->print_weapons(label);
				this->print_armor(label);
			}
			return;
		}

};


#endif /* INVENTORY_HPP */
