/* Validate weapons : Wand/Staff/Magic Ring  --- Possible weapons : Bow/Sword/Hammer/Axe/Club */

#ifndef _ITEM_H_
#define _ITEM_H_

/*=== Avoid mutual inclusions ===*/
class Inventory;

/*=== Enumerations ===*/

enum ItemCategories { NO_ITEM, ARMOR, PRIMARY_WEAPON, SECONDARY_WEAPON };
enum WeaponCategories { NO_WEAPON, WAND, STAFF, MAGIC_RING, SHIELD };
enum ArmorCategories { HAT, CLOAK, CHEST, BELT, PANTS, BOOTS, GLOVE_1, GLOVE_2, NECKLESS, EARING_1, EARING_2, RING_1, RING_2, NO_ARMOR };
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

	/* Equips @this */
	virtual void equips(Inventory *inventory);

	/*=== Getters ===*/
	
	/* Name */
	virtual std::string getName() const;
	/* Category */
	virtual ItemCategories getCategory() const;
	/* Category (string not enum [for display]) */
	virtual std::string showCategory() const;

protected:

	std::string m_name;
	ItemCategories m_category;
};

#endif // !_ITEM_H_

