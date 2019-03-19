#ifndef _WEAPON_H_
#define _WEAPON_H_

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

	/*=== Getters ===*/

	/* Damage */
	int getDamage() const;
	/* WeaponCategory */
	virtual WeaponCategories getWeaponCategory() const;
	/* WeaponCategory (string not enum [for display]) */
	virtual std::string showCategory() const;

private:

	int m_damage;
	WeaponCategories m_weaponCategory;
};

#endif // !_WEAPON_H_
