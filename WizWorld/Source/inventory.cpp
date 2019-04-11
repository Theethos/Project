#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Inventory.h"


/* Constructors */
Inventory::Inventory() : hand_1(0), hand_2(0), bag(0), stuff(0), size(15), firstFreeSlot(0)
{
	this->hand_1 = new Weapon("Grandma's wand", ItemCategories::PRIMARY_WEAPON, WeaponCategories::WAND, 10);
	this->hand_2 = new Weapon("Wooden shield", ItemCategories::SECONDARY_WEAPON, WeaponCategories::SHIELD, 5);

	this->stuff = new Armor*[static_cast<int>(ArmorCategories::RING_2)];
	this->bag = new Item*[this->size];

	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		this->stuff[i] = nullptr;
	}
	for (int i = 0; i < this->size; i++)
	{
		this->bag[i] = nullptr;
	}
}

Inventory::Inventory(std::string primaryWeaponName, ItemCategories primaryWeaponCategory, 
					 WeaponCategories weaponCategory, int primaryWeaponDamage) : hand_1(0), hand_2(0), bag(0), stuff(0), size(15), firstFreeSlot(0)
{
	this->hand_1 = new Weapon(primaryWeaponName, primaryWeaponCategory, weaponCategory, primaryWeaponDamage);
	this->hand_2 = new Weapon("Wooden shield", ItemCategories::NO_ITEM, WeaponCategories::SHIELD, 5);

	this->stuff = new Armor*[static_cast<int>(ArmorCategories::RING_2)];
	this->bag = new Item*[this->size];

	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		this->stuff[i] = nullptr;
	}
	for (int i = 0; i < this->size; i++)
	{
		this->bag[i] = nullptr;
	}
};

/* Destructor */
Inventory::~Inventory()
{
	delete this->hand_1;
	delete this->hand_2;
	delete this->bag;
	delete this->stuff;
}

/* Returns FALSE if a slot is available in the bag and set the firstFreeIndex if so. */
bool Inventory::isFull()
{
	for (int i = 0; i < this->size; i++)
	{
		if (!this->bag[i])
		{
			this->firstFreeSlot = i;
			return false;
		}
	}
	return true;
}

void Inventory::removeFromBag(Item * item)
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->bag[i] == item)
		{
			this->bag[i] = nullptr;
			break;
		}
	}
}

void Inventory::removeFromStuff(Item * item)
{
	if (!isFull())
	{
		this->bag[this->firstFreeSlot] = item;
		this->stuff[static_cast<int>(item->getCategory())] = nullptr;
	}
	else
	{
		// Nothing for now
		return;
	}
}

/* Check if the item is in the bag and if so, returns its index in the bag, else return -1 */
int Inventory::isInBag(Item * item)
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->bag[i] == item)
		{
			return i;
		}
	}
	return -1;
}

/* Getters */
Weapon* Inventory::getWeapon_1() const
{
	return this->hand_1;
}

Weapon* Inventory::getWeapon_2() const
{
	return this->hand_2;
}

Item ** Inventory::getBag() const
{
	return this->bag;
}

Armor ** Inventory::getStuff() const
{
	return this->stuff;
}

int Inventory::getSize() const
{
	return this->size;
}

/* Setters */
// Puts the item in the bag if it is not full
void Inventory::setBag(Item * item)
{
	if (!isFull())
	{
		this->bag[this->firstFreeSlot] = item;
	}
	else
	{
		std::cout << "Bag is full" << std::endl;
	}
}

// Equips the weapon in primary hand
void Inventory::setWeapon_1(Weapon * weapon)
{	
	// If there is already a weapon in the primary_hand
	if (this->hand_1)
	{
		// Check if it was an invalid weapon, and if so, puts the weapon in the slot
		if (this->hand_1->getCategory() == ItemCategories::NO_ITEM)
		{
			*this->hand_1 = *weapon;
		}
		// Else it switches both weapons (weapon goes in the stuff and the previous weapon goes in the bag)
		else
		{
			int index = isInBag(weapon);
			if (index >= 0)
			{
				SWAP_VALUE(this->hand_1, weapon);
			}
		}
	}
	// Else the slot is free, so it puts the armor in the stuff (and remove it from bag)
	else
	{
		this->hand_2 = weapon;
		int index = isInBag(weapon);
		if (index >= 0)
		{
			this->bag[index] = nullptr;
		}
	}
}

// Equips the weapon in secondary hand
void Inventory::setWeapon_2(Weapon * weapon)
{
	// Same as setWeapon_1
	if (this->hand_2)
	{
		if (this->hand_2->getCategory() == ItemCategories::NO_ITEM)
		{
			*this->hand_2 = *weapon;
		}
		else
		{
			int index = isInBag(weapon);
			if (index >= 0)
			{
				SWAP_VALUE(this->hand_2, weapon);
			}
		}
	}
	else
	{
		this->hand_2 = weapon;
		int index = isInBag(weapon);
		if (index >= 0)
		{
			this->bag[index] = nullptr;
		}
	}
}

// Equips the item
void Inventory::setStuff(Armor *armor)
{
	// If there is already an armor in that slot
	if (this->stuff[static_cast<int>(armor->getArmorCategory())])
	{
		// Check if it was an invalid armor
		if (this->stuff[static_cast<int>(armor->getArmorCategory())]->getCategory() == ItemCategories::NO_ITEM)
		{
			*this->stuff[static_cast<int>(armor->getArmorCategory())] = *armor;
		}
		// Else it switches both armors (armor goes in the stuff and the previous armor goes in the bag)
		else
		{
			int index = isInBag(armor);
			if (index >= 0)
			{
				SWAP_VALUE(this->stuff[static_cast<int>(armor->getArmorCategory())], armor);
			}
		}
	}
	// Else the slot is free, so it puts the armor in the stuff (and remove it from bag)
	else
	{
		this->stuff[static_cast<int>(armor->getArmorCategory())] = armor;
		int index = isInBag(armor);
		if (index >= 0)
		{
			this->bag[index] = nullptr;
		}
	}
}

