#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Macros_Includes.h"
#include "Item.h"
#include "Inventory.h"

/*
 * ==================================================
 * ================ Class Weapon ====================
 * ==================================================
 */

class Weapon : public Item
{
public:
	/*=== Constructors/Destructor ===*/

	Weapon();
	Weapon(std::string name, ItemCategories category, WeaponCategories weaponCategory, int damage);
	Weapon(const Weapon &weapon);
	virtual ~Weapon();

	/*=== Operator overload ===*/

	Weapon &operator=(const Weapon &weapon);

	/*=== Methods ===*/

	/* Equips an item */
	virtual void equips(Inventory *inventory);

	/*=== Getters ===*/

	/* Damage */
	int getDamage() const;
	virtual std::string showCategory() const;

private:

	int m_damage;
	WeaponCategories m_weaponCategory;
};

#endif // !_WEAPON_H_
