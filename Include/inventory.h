#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	/* Methods*/
	bool isFull();
	void showInventory();

	/* Getters */
	Weapon *getWeapon_1() const;
	Weapon *getWeapon_2() const;

	/* Setters */
	void setBag(Item *item);
	void setWeapon_1(Weapon *weapon);
	void setWeapon_2(Weapon *weapon);
	void setStuff(Item *item);

private:
	Weapon *m_hand_1;
	Weapon *m_hand_2;
	Item **m_stuff;
	int m_size; // = 15 (items in the bag)
	Item **m_bag;
	int m_firstFreeSlot;
};

#endif // !INVENTORY_H
