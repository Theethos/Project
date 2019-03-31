#include "../Include/Macro_Include.h"
#include "../Include/Inventory.h"


/* Constructors */
Inventory::Inventory() : m_hand_1(0), m_hand_2(0), m_bag(0), m_stuff(0), m_size(15), m_firstFreeSlot(0)
{
	m_hand_1 = new Weapon("Grandma's wand", ItemCategories::PRIMARY_WEAPON, WeaponCategories::WAND, 10);
	m_hand_2 = new Weapon("Wooden shield", ItemCategories::SECONDARY_WEAPON, WeaponCategories::SHIELD, 5);

	m_stuff = new Armor*[static_cast<int>(ArmorCategories::RING_2)];
	m_bag = new Item*[m_size];

	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		m_stuff[i] = nullptr;
	}
	for (int i = 0; i < m_size; i++)
	{
		m_bag[i] = nullptr;
	}
}

Inventory::Inventory(std::string primaryWeaponName, ItemCategories primaryWeaponCategory, 
					 WeaponCategories weaponCategory, int primaryWeaponDamage) : m_hand_1(0), m_hand_2(0), m_bag(0), m_stuff(0), m_size(15), m_firstFreeSlot(0)
{
	m_hand_1 = new Weapon(primaryWeaponName, primaryWeaponCategory, weaponCategory, primaryWeaponDamage);
	m_hand_2 = new Weapon("Wooden shield", ItemCategories::NO_ITEM, WeaponCategories::SHIELD, 5);

	m_stuff = new Armor*[static_cast<int>(ArmorCategories::RING_2)];
	m_bag = new Item*[m_size];

	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		m_stuff[i] = nullptr;
	}
	for (int i = 0; i < m_size; i++)
	{
		m_bag[i] = nullptr;
	}
};

/* Destructor */
Inventory::~Inventory()
{
	delete m_hand_1;
	delete m_hand_2;
	delete m_bag;
	delete m_stuff;
}

/* Returns FALSE if a slot is available in the bag and set the firstFreeIndex if so. */
bool Inventory::isFull()
{
	for (int i = 0; i < m_size; i++)
	{
		if (!m_bag[i])
		{
			m_firstFreeSlot = i;
			return false;
		}
	}
	return true;
}

void Inventory::removeFromBag(Item * item)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_bag[i] == item)
		{
			m_bag[i] = nullptr;
			break;
		}
	}
}

void Inventory::removeFromStuff(Item * item)
{
	if (!isFull())
	{
		m_bag[m_firstFreeSlot] = item;
		m_stuff[static_cast<int>(item->getCategory())] = nullptr;
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
	for (int i = 0; i < m_size; i++)
	{
		if (m_bag[i] == item)
		{
			return i;
		}
	}
	return -1;
}

/* Getters */
Weapon* Inventory::getWeapon_1() const
{
	return m_hand_1;
}

Weapon* Inventory::getWeapon_2() const
{
	return m_hand_2;
}

Item ** Inventory::getBag() const
{
	return m_bag;
}

Armor ** Inventory::getStuff() const
{
	return m_stuff;
}

int Inventory::getSize() const
{
	return this->m_size;
}

/* Setters */
// Puts the item in the bag if it is not full
void Inventory::setBag(Item * item)
{
	if (!isFull())
	{
		m_bag[m_firstFreeSlot] = item;
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
	if (m_hand_1)
	{
		// Check if it was an invalid weapon, and if so, puts the weapon in the slot
		if (m_hand_1->getCategory() == ItemCategories::NO_ITEM)
		{
			*m_hand_1 = *weapon;
		}
		// Else it switches both weapons (weapon goes in the stuff and the previous weapon goes in the bag)
		else
		{
			int index = isInBag(weapon);
			if (index >= 0)
			{
				SWAP_VALUE(m_hand_1, weapon);
			}
		}
	}
	// Else the slot is free, so it puts the armor in the stuff (and remove it from bag)
	else
	{
		m_hand_2 = weapon;
		int index = isInBag(weapon);
		if (index >= 0)
		{
			m_bag[index] = nullptr;
		}
	}
}

// Equips the weapon in secondary hand
void Inventory::setWeapon_2(Weapon * weapon)
{
	// Same as setWeapon_1
	if (m_hand_2)
	{
		if (m_hand_2->getCategory() == ItemCategories::NO_ITEM)
		{
			*m_hand_2 = *weapon;
		}
		else
		{
			int index = isInBag(weapon);
			if (index >= 0)
			{
				SWAP_VALUE(m_hand_2, weapon);
			}
		}
	}
	else
	{
		m_hand_2 = weapon;
		int index = isInBag(weapon);
		if (index >= 0)
		{
			m_bag[index] = nullptr;
		}
	}
}

// Equips the item
void Inventory::setStuff(Armor *armor)
{
	// If there is already an armor in that slot
	if (m_stuff[static_cast<int>(armor->getArmorCategory())])
	{
		// Check if it was an invalid armor
		if (m_stuff[static_cast<int>(armor->getArmorCategory())]->getCategory() == ItemCategories::NO_ITEM)
		{
			*m_stuff[static_cast<int>(armor->getArmorCategory())] = *armor;
		}
		// Else it switches both armors (armor goes in the stuff and the previous armor goes in the bag)
		else
		{
			int index = isInBag(armor);
			if (index >= 0)
			{
				SWAP_VALUE(m_stuff[static_cast<int>(armor->getArmorCategory())], armor);
			}
		}
	}
	// Else the slot is free, so it puts the armor in the stuff (and remove it from bag)
	else
	{
		m_stuff[static_cast<int>(armor->getArmorCategory())] = armor;
		int index = isInBag(armor);
		if (index >= 0)
		{
			m_bag[index] = nullptr;
		}
	}
}

