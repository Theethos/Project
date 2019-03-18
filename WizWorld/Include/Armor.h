#ifndef _ARMOR_H_
#define _ARMOR_H_

/*
 * ==================================================
 * ================ Class Armor =====================
 * ==================================================
 */

class Armor : public Item
{
public:
	/*=== Constructors/Destructor ===*/

	Armor();
	Armor(std::string name, ItemCategories category, ArmorCategories weaponCategory);
	Armor(const Armor &armor);
	virtual ~Armor();

	/*=== Operator overload ===*/

	Armor &operator=(const Armor &armor);

	/*=== Methods ===*/

	/* Equips @this */
	virtual void equips(Inventory *inventory);

	/*=== Getters ===*/

	/* ArmorCategory */
	virtual ArmorCategories getArmorCategory() const;
	/* ArmorCategory (string not enum [for display]) */
	virtual std::string showCategory() const;

private:
	ArmorCategories m_armorCategory;
};

#endif // !_ARMOR_H_



