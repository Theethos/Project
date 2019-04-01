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
	Armor();
	Armor(std::string name, ItemCategories category, ArmorCategories weaponCategory);
	Armor(const Armor &armor);
	virtual ~Armor();

	Armor &operator=(const Armor &armor);

	/* Getters */
	ArmorCategories getArmorCategory() const;
	std::string showCategory() const;

private:
	ArmorCategories m_armorCategory;
};

#endif // !_ARMOR_H_



