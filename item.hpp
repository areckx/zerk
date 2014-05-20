// File: item.hpp
// Description: [Items class for Zerk]
// Last Modified: 2014-05-16Fri 10:43 PDT
//
// HEADER GUARDS
// ** used to protect against class, variable, and function definition clashes.
// ** tells the preprocessor to only include this file ONCE
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

// We could name individual properties to the Item class, but it's not good design.
// Instead we will add to the Item class the properties that are common among all 
// items: weapons, armor, coins, etc., and then make separate weapons and armor classes
// which will `inherit` their properties from the base Item class
//
// Every Item needs:
// 	* a name to identify it 
// 	* a description of what it looks like or does
// 	* possibly add weight(TODO)
class Item 
{

	public:

		Item() 
		{

		}

		// Name and description of the item
		std::string name;
		std::string description;

		// Standard constructor, nothing special
		Item(std::string name, std::string description) 
		{
			this->name = name;
			this->description = description;

		}
};




#endif /* ITEM_HPP */
