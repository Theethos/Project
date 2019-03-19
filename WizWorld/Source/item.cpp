#include "../Include/Macros_Includes.h"

#include "../Include/Item.h"

/*
 * ==================================================
 * ================= Class Item =====================
 * ==================================================
 */

/* Constructors */
Item::Item() : m_name("NULL"), m_category(NO_ITEM)
{}
Item::Item(std::string name, ItemCategories category) : m_name(name), m_category(category)
{}
Item::Item(const Item & item)
{
	m_category = item.m_category;
	m_name = item.m_name;
}

/* Destructor */
Item::~Item()
{}

/*=== Operator overload ===*/

/* operator '=' */
Item & Item::operator=(const Item & item)
{
	m_category = item.m_category;
	m_name = m_name;

	return *this;
}

/*=== Getters ===*/

/* Name */
std::string Item::getName() const
{
	return m_name;
}
/* Category */
ItemCategories Item::getCategory() const
{
	return m_category;
}
/* Category (string not enum [for display]) */
std::string Item::showCategory() const
{
	switch (m_category)
	{
	case NO_ITEM:
		return "None";
		break;
	case ARMOR:
		return "Armor";
		break;
	case PRIMARY_WEAPON:
		return "Primary Weapon";
		break;
	case SECONDARY_WEAPON:
		return "Secondary Weapon";
		break;
	default:
		return "None";
		break;
	}
}
