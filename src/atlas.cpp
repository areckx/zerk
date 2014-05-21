// File: atlas.cpp
// Description: [non-header function for Atlas in Zerk]
// Last Modified: 2014-05-16Fri 10:43 PDT
// TODO :: Make config files for this data to easily add new content ::
//
#include "atlas.hpp"

void buildatlas_creature(std::vector<Creature>& atlas)
{
	// Fill the atlas
	// Creature(name, hp, str, vit, dex, hitRate, level)
	atlas.push_back(Creature("Rat", 8, 8, 8, 12, 2.0, 1)); 

	return;
}

void buildatlas_item(std::vector<Item>& atlas)
{
	// Item(name, description)
	atlas.push_back(Item("Gold Coin",
		"A small disk made of luxurious metal."));

	atlas.push_back(Item("Iron Key",
		"A heavy iron key with a simple cut."));

	return;
}

void buildatlas_weapon(std::vector<Weapon>& atlas)
{
	// Weapon(name, description, damage, hitRate
	atlas.push_back(Weapon("Iron Dagger",
		"A short blade made of iron with a leather bound hilt.",
		5, 10.0));

	atlas.push_back(Weapon("Excalibur",
		"The legendary blade, bestowed upon you by the Lady of the Lake.",
		35, 35.0));

	return;
}

void buildatlas_armor(std::vector<Armor>& atlas)
{
	// Armor(name, description, defense, slot)
	atlas.push_back(Armor("Leather Cuirass",
		"Torso armor made of tanned hide.", 4, Armor::Slot::TORSO));

	return;
}

void buildatlas_area(std::vector<Area>& atlas,
		std::vector<Item>& items, std::vector<Weapon>& weapons,
		std::vector<Armor>& armor, std::vector<Creature>& creatures)
{
	// Area definitions are somewhat more complicated:
	atlas.push_back(Area(Dialogue(			// Standard dialogue definition
		"You are in room 1",			// Description
		{"Go to room 2", "Search"}),		// Choices
		Inventory(				// Area inventory
		{
			std::make_pair(&items[0], 5)	// Pair of item and quantity
		},
		{
			std::make_pair(&weapons[0], 1)	// Pair of weapon and quantity
		},
		{
			std::make_pair(&armor[0], 1)	// Pair of armor and quantity
		}),
		{					// Creatures
		}));

	atlas.push_back(Area(Dialogue(
		"You are in room 2",
		{"Go to room 1", "Search"}),
		Inventory(
		{
			std::make_pair(&items[0], 10),
			std::make_pair(&items[1], 1)
		},
		{
		},
		{
		}),
		{
			&creatures[0]
		}));
	return;
}
