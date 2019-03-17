/* Validate weapons : Wand/Staff/Magic Ring  --- Possible weapons : Bow/Sword/Hammer/Axe/Club */

#ifndef ITEM_H
#define ITEM_H

class Inventory;

/*=== Enumerations ===*/
					// Items																										 // Weapons
enum ItemCategories { NO_ITEM, HAT, CLOAK, CHEST, BELT, PANTS, BOOTS, GLOVE_1, GLOVE_2, NECKLESS, EARING_1, EARING_2, RING_1, RING_2, PRIMARY_WEAPON, SECONDARY_WEAPON };
enum WeaponCategories { NO_WEAPON, WAND, STAFF, MAGIC_RING, SHIELD };
/*
 * ==================================================
 * ================= Class Item =====================
 * ==================================================
 */

class Item
{
public:
	/*=== Constructors/Destructor ===*/

	Item();
	Item(std::string name, ItemCategories category);
	Item(const Item &item);
	virtual ~Item();

	/*=== Operator overload ===*/

	Item &operator=(const Item &item);

	/*=== Methods ===*/

	/* Equips an item */
	virtual void equips(Inventory *inventory);

	/*=== Getters ===*/
	
	/* Name */
	virtual std::string getName() const;
	/* Category */
	ItemCategories getCategory() const;
	/* Category (string not enum [for display]) */
	virtual std::string showCategory() const;

protected:

	std::string m_name;
	ItemCategories m_category;
};


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

#endif // !ITEM_H

