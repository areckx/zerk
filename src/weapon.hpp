// File: weapon.hpp
// Description: [Weapons class for Zerk]
// Last Modified: 2014-05-16Fri 10:43 PDT
//
#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "item.hpp"

#include <string>

// Weapons are items, so they should inherit their properties
//
// Properties of a weapon :
// 	* damage 
// 	* hitRate
class Weapon : public Item 
{

	public:
		Weapon() 
		{

		}

		// Weapon damage. See the Battle class for formula, but
		// values between 1~50 are reasonable
		unsigned damage;

		// Modifier to hit change. Small values are encouraged, e.g.
		// 5~30%
		double hitRate;

		// Pass inherited qualities to the normal line construction
		Weapon (std::string name, std::string description,
			int damage, double hitRate) : Item(name, description) 
	{

			this->damage = damage;
			this->hitRate = hitRate; 
		}

};


#endif /* WEAPON_HPP */
