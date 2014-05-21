// File: atlas.hpp
// Description: [Atlas function of Zerk]
// Last Modified: 2014-05-16Fri 10:43 PDT
//
#ifndef ATLAS_HPP
#define ATLAS_HPP

#include <vector>

#include "creature.hpp"
#include "item.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "area.hpp"

// Atlas building functions. Atlases contain vectors of game data
// that is not modified in gameplay, so the base versions of
// creatures, items, etc. could easily be replaced with functions
// that load the information from config files instead of just 
// defining the values in code.
void buildatlas_creature(std::vector<Creature>& atlas);
void buildatlas_item(std::vector<Item>& atlas);
void buildatlas_weapon(std::vector<Weapon>& atlas);
void buildatlas_armor(std::vector<Armor>& atlas);
void buildatlas_area(std::vector<Area>& atlas,
		std::vector<Item>& items, std::vector<Weapon>& weapons,
		std::vector<Armor>& armor, std::vector<Creature>& creatures);


#endif /* ATLAS_HPP */
