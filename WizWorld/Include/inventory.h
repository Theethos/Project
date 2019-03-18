#ifndef _INVENTORY_H_
#define _INVENTORY_H_

/*=== Avoid mutual inclusions ===*/
class Item;
class Weapon;
class Armor;
enum ItemCategories;
enum WeaponCategories;
enum ArmorCategories;

/* 
 * ==================================================
 * ================= Class Inventory ================
 * ==================================================
 */

class Inventory
{
public:
	/*=== Constructors/Destructor ===*/

	Inventory();
	Inventory(std::string primaryWeaponName, ItemCategories primaryWeaponCategory, WeaponCategories weaponCategory, int primaryWeaponDamage);
	virtual ~Inventory();

	/*=== Methods ===*/

	/* Returns FALSE if a slot is available in the bag and set @member[firstFreeIndex] if so. */
	bool isFull();
	/* Equips @param[item] (item or weapon) */
	void equipItem(Item *item);
	/* Removes @param[item] of the @member[bag] */
	void removeBag(Item *item);
	/* Removes @param[item] of the @member[stuff] */
	void removeStuff(Item *item);
	/* Check if @param[item] is in @member[bag] and if so returns its index in the bag */
	int isInBag(Item *item);

	/*=== Getters ===*/

	/* Primary hand */
	Weapon* getWeapon_1() const;
	/* Secondary hand */
	Weapon* getWeapon_2() const;
	/* Bag */
	Item** getBag() const;
	/* Stuff*/
	Armor** getStuff() const;
	/* Size */
	int getSize() const;

	/*=== Setters ===*/

	/* Puts @param[item] in @membre[bag] if it is not full */
	void setBag(Item *item);
	/* Equips @param[weapon] in primary hand */
	void setWeapon_1(Weapon *weapon);
	/* Equips @param[weapon] in secondary hand */
	void setWeapon_2(Weapon *weapon);
	/* Equips @param[item] */
	void setStuff(Armor *armor);

private:
	/* Weapon in primary hand  */
	Weapon *m_hand_1;
	/* Weapon in secondary hand */
	Weapon *m_hand_2;
	/* Items equiped by the character */
	Armor **m_stuff;
	/* Number of slots in the @member[bag] */
	int m_size;
	/* Item carryed by the character */
	Item **m_bag;
	/* 1st slot available in the @member[bag] */
	int m_firstFreeSlot;
};

#endif // !_INVENTORY_H_
