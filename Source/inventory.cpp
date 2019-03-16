#include "../Include/inventory.h"

#include <iostream>

using namespace std;

Inventory::Inventory() : m_size(15), m_firstFreeSlot(0)
{
	m_hand_1 = new Weapon;
	m_hand_2 = new Weapon;
	m_stuff = new Item*[RING_2];
	m_bag = new Item*[m_size];
	for (int i = 0; i < RING_2; i++)
	{
		m_stuff[i] = new Item;
	}
	for (int i = 0; i < m_size; i++)
	{
		m_bag[i] = new Item;
	}
}

Inventory::~Inventory()
{
	delete m_hand_1;
	delete m_hand_2;
	for (int i = 0; i < RING_2; i++)
	{
		delete m_stuff[i];
	}
	for (int i = 0; i < m_size; i++)
	{
		delete m_bag[i];
	}
}

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

void Inventory::showInventory()
{	
	cout << "Bag : ";
	for (int i = 0; i < m_size; i++)
	{
		cout << m_bag[i]->getName() << "-->";
	}
	cout << endl << "      ";
	for (int i = 0; i < m_size; i++)
	{
		cout << m_bag[i]->getCategory() << "-->";
	}
	cout << endl << endl << "Stuff : ";
	for (int i = 0; i < RING_2; i++)
	{
		cout << m_stuff[i]->getName() << "-->";
	}
	cout << endl << "      ";
	for (int i = 0; i < RING_2; i++)
	{
		cout << m_stuff[i]->getCategory() << "-->";
	}
}

Weapon* Inventory::getWeapon_1() const
{
	return m_hand_1;
}

Weapon * Inventory::getWeapon_2() const
{
	return m_hand_2;
}
// Puts the item in the bag if possible
void Inventory::setBag(Item * item)
{
	if (!isFull())
	{
		m_bag[m_firstFreeSlot] = item;
	}
	else
	{
		cout << "Bag is full" << endl;
	}
}
// Equips the weapon in slot_weapon_1
void Inventory::setWeapon_1(Weapon * weapon)
{
	if (!m_hand_1)
	{
		m_hand_1 = weapon;
	}
	else
	{
		Weapon tmp = *weapon;
		*weapon = *m_hand_1;
		*m_hand_1 = tmp;
	}
}
// Equips the weapon in slot_weapon_2
void Inventory::setWeapon_2(Weapon * weapon)
{
	if (!m_hand_2)
	{
		m_hand_2 = weapon;
	}
	else
	{
		Weapon tmp(*weapon);
		*weapon = *m_hand_2;
		*m_hand_2 = tmp;
	}
}
// Equips the item
void Inventory::setStuff(Item *item)
{
	if (!m_stuff[item->getCategory()])
	{
		m_stuff[item->getCategory()] = item;
	}
	else
	{
		Item tmp(*item);
		*item = *m_stuff[item->getCategory()];
		*m_stuff[item->getCategory()] = tmp;
	}
}

