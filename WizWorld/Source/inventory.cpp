#include "../Include/Macros_Includes.h"
#include "../Include/Item.h"
#include "../Include/Weapon.h"
#include "../Include/Armor.h"

#include "../Include/Inventory.h"

/*
 * ==================================================
 * ================= Class Inventory ================
 * ==================================================
 */

/* Constructors */
Inventory::Inventory() : m_hand_1(0), m_hand_2(0), m_bag(0), m_stuff(0), m_size(15), m_firstFreeSlot(0)
{
	m_hand_1 = new Weapon("Grandma's wand", PRIMARY_WEAPON, WAND, 10);
	m_hand_2 = new Weapon("Wooden shield", SECONDARY_WEAPON, SHIELD, 5);

	m_stuff = new Armor*[(int)RING_2];
	m_bag = new Item*[m_size];

	for (int i = 0; i < (int)RING_2; i++)
	{
		m_stuff[i] = nullptr;
	}
	for (int i = 0; i < m_size; i++)
	{
		m_bag[i] = nullptr;
	}
}
Inventory::Inventory(std::string primaryWeaponName, ItemCategories primaryWeaponCategory, WeaponCategories weaponCategory, int primaryWeaponDamage) : m_hand_1(0), m_hand_2(0), m_bag(0), m_stuff(0), m_size(15), m_firstFreeSlot(0)
{
	m_hand_1 = new Weapon(primaryWeaponName, primaryWeaponCategory, weaponCategory, primaryWeaponDamage);
	m_hand_2 = new Weapon("Wooden shield", NO_ITEM, SHIELD, 5);

	m_stuff = new Armor*[(int)RING_2];
	m_bag = new Item*[m_size];

	for (int i = 0; i < (int)RING_2; i++)
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
/*=== Methods ===*/

/* Returns FALSE if a slot is available in the bag and set @member[firstFreeIndex] if so. */
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

void Inventory::equipItem(Item * item)
{
	item->equips(this);
}

void Inventory::removeBag(Item * item)
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

void Inventory::removeStuff(Item * item)
{
	if (!isFull())
	{
		m_bag[m_firstFreeSlot] = item;
		m_stuff[item->getCategory()] = nullptr;
	}
	else
	{
		// Nothing for now
		return;
	}
}

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

/*=== Getters ===*/

/* Primary hand */
Weapon* Inventory::getWeapon_1() const
{
	return m_hand_1;
}
/* Secondary hand */
Weapon* Inventory::getWeapon_2() const
{
	return m_hand_2;
}
/* Bag */
Item ** Inventory::getBag() const
{
	return m_bag;
}
/* Stuff */
Armor ** Inventory::getStuff() const
{
	return m_stuff;
}

int Inventory::getSize() const
{
	return this->m_size;
}

/*=== Setters ===*/

/* Puts @param[item] in the bag if it is not full */
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
/* Equips @param[weapon] in primary hand */
void Inventory::setWeapon_1(Weapon * weapon)
{	
	if (m_hand_1->getCategory() == NO_ITEM)
	{
		*m_hand_1 = *weapon;
	}
	else
	{
		int index = isInBag(weapon);
		if (index >= 0)
		{
			SWAP_VALUE(m_hand_1, weapon);
		}
	}
}
/* Equips @param[weapon] in secondary hand */
void Inventory::setWeapon_2(Weapon * weapon)
{
	if (m_hand_2->getCategory() == NO_ITEM)
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
/* Equips @param[item] */
void Inventory::setStuff(Armor *armor)
{
	if (m_stuff[armor->getArmorCategory()])
	{
		if (m_stuff[armor->getArmorCategory()]->getCategory() == NO_ITEM)
		{
			*m_stuff[armor->getArmorCategory()] = *armor;
		}
		else
		{
			int index = isInBag(armor);
			if (index >= 0)
			{
				SWAP_VALUE(m_stuff[armor->getArmorCategory()], armor);
			}
		}
	}
	else
	{
		m_stuff[armor->getArmorCategory()] = armor;
		int index = isInBag(armor);
		if (index >= 0)
		{
			m_bag[index] = nullptr;
		}

	}
}

