#include "../Include/Macros_Includes.h"
#include "../Include/Item.h"
#include "../Include/Weapon.h"

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

	m_stuff = new Item*[(int)RING_2];
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

	m_stuff = new Item*[(int)RING_2];
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

void Inventory::removeItem(Item * item)
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
Item ** Inventory::getStuff() const
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
	if (m_hand_1)
	{
		if (m_hand_1->getCategory() == NO_ITEM)
		{
			m_hand_1 = weapon;
			removeItem(weapon);
		}
		else
		{
			/*Weapon *tmp = m_hand_1;
			m_hand_1 = weapon;
			weapon = tmp;*/
			SWAP_POINTERS(m_hand_1, weapon);
		}
	}
	else
	{
		m_hand_1 = weapon;
	}
}
/* Equips @param[weapon] in secondary hand */
void Inventory::setWeapon_2(Weapon * weapon)
{
	if (m_hand_2)
	{
		if (m_hand_2 && m_hand_2->getCategory() == NO_ITEM)
		{
			m_hand_2 = weapon;
			removeItem(weapon);
		}
		else
		{
			SWAP_POINTERS(m_hand_2, weapon);
		}
	}
	else
	{
		m_hand_2 = weapon;
	}
}
/* Equips @param[item] */
void Inventory::setStuff(Item *item)
{
	if (!m_stuff[item->getCategory()])
	{
		m_stuff[item->getCategory()] = item;
	}
	else
	{
		Item *tmp = m_stuff[item->getCategory()];
		m_stuff[item->getCategory()] = item;
		if (tmp->getCategory() != NO_ITEM)
			m_stuff[item->getCategory()] = tmp;
	}
}

