#include "../Include/Macros_Includes.h"
#include "../Include/Item.h"
#include "../Include/Inventory.h"

#include "../Include/Armor.h"

/*
 * ==================================================
 * ================ Class Armor =====================
 * ==================================================
 */

/* Constructors */
Armor::Armor() : Item(), m_armorCategory(NO_ARMOR)
{}
Armor::Armor(std::string name, ItemCategories category, ArmorCategories armorCategory) : Item(name, category), m_armorCategory(armorCategory)
{}

Armor::Armor(const Armor & armor)
{
	m_name = armor.m_name;
	m_category = armor.m_category;
	m_armorCategory = armor.m_armorCategory;
}
/* Destructor */
Armor::~Armor()
{}

/*=== Operator overload ===*/

/* operator '=' */
Armor & Armor::operator=(const Armor & armor)
{
	m_name = armor.m_name;
	m_category = armor.m_category;
	m_armorCategory = armor.m_armorCategory;

	return *this;
}
/* Equips @this */
void Armor::equips(Inventory * inventory)
{
	inventory->setStuff(this);
}
/* ArmorCategory */
ArmorCategories Armor::getArmorCategory() const
{
	return m_armorCategory;
}
/* ArmorCategory (string not enum [for display]) */
std::string Armor::showCategory() const
{
	switch (m_armorCategory)
	{
		case NO_ARMOR:
			return "None";
			break;
		case HAT:
			return "Hat";
			break;
		case CLOAK:
			return "Cloak";
			break;
		case CHEST:
			return "Chest";
			break;
		case BELT:
			return "Belt";
			break;
		case PANTS:
			return "Pants";
			break;
		case BOOTS:
			return "Boots";
			break;
		case GLOVE_1:
			return "Gloves";
			break;
		case GLOVE_2:
			return "Gloves";
			break;
		case NECKLESS:
			return "Neckless";
			break;
		case EARING_1:
			return "Earings";
			break;
		case EARING_2:
			return "Earings";
			break;
		case RING_1:
			return "Ring";
			break;
		case RING_2:
			return "Ring";
			break;
		default:
			return "None";
			break;
	}
}
