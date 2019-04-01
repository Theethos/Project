#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

class Inventory
{
public:
	Inventory();
	Inventory(std::string primaryWeaponName, ItemCategories primaryWeaponCategory, WeaponCategories weaponCategory, int primaryWeaponDamage);
	virtual ~Inventory();

	bool isFull();
	int isInBag(Item *item);
	void removeFromBag(Item *item);
	void removeFromStuff(Item *item);

	/* Getters */
	Weapon* getWeapon_1() const;
	Weapon* getWeapon_2() const;
	Item** getBag() const;
	Armor** getStuff() const;
	int getSize() const;

	/* Setters */
	void setBag(Item *item);
	void setWeapon_1(Weapon *weapon);
	void setWeapon_2(Weapon *weapon);
	void setStuff(Armor *armor);

private:
	// Weapon in primary hand
	Weapon *m_hand_1;
	// Weapon in secondary hand
	Weapon *m_hand_2;
	// Items equiped by the character
	Armor **m_stuff;
	// Number of slots in the bag
	int m_size;
	// Item carryed by the character
	Item **m_bag;
	// First slot available in the bag
	int m_firstFreeSlot;
};

#endif // !_INVENTORY_H_
