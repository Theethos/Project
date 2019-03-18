#include "../Include/Macros_Includes.h"
#include "../Include/Inventory.h"

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

void Item::equips(Inventory *inventory)
{
	inventory->setStuff(this);
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

std::string Item::showCategory() const
{
	switch (m_category)
	{
	case NO_ITEM:
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
