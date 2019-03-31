#include "../Include/Macro_Include.h"
#include "../Include/Item.h"
#include "../Include/Armor.h"

/* Constructors */
Armor::Armor() : Item(), m_armorCategory(ArmorCategories::NO_ARMOR)
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

Armor & Armor::operator=(const Armor & armor)
{
	m_name = armor.m_name;
	m_category = armor.m_category;
	m_armorCategory = armor.m_armorCategory;

	return *this;
}
/* Getters */
ArmorCategories Armor::getArmorCategory() const
{
	return m_armorCategory;
}

/* ArmorCategory (string not enum [for display]) */
std::string Armor::showCategory() const
{
	switch (m_armorCategory)
	{
		case ArmorCategories::NO_ARMOR:
			return "None";
			break;
		case ArmorCategories::HAT:
			return "Hat";
			break;
		case ArmorCategories::CLOAK:
			return "Cloak";
			break;
		case ArmorCategories::CHEST:
			return "Chest";
			break;
		case ArmorCategories::BELT:
			return "Belt";
			break;
		case ArmorCategories::PANTS:
			return "Pants";
			break;
		case ArmorCategories::BOOTS:
			return "Boots";
			break;
		case ArmorCategories::GLOVE_1:
			return "Gloves";
			break;
		case ArmorCategories::GLOVE_2:
			return "Gloves";
			break;
		case ArmorCategories::NECKLESS:
			return "Neckless";
			break;
		case ArmorCategories::EARING_1:
			return "Earings";
			break;
		case ArmorCategories::EARING_2:
			return "Earings";
			break;
		case ArmorCategories::RING_1:
			return "Ring";
			break;
		case ArmorCategories::RING_2:
			return "Ring";
			break;
		default:
			return "None";
			break;
	}
}
