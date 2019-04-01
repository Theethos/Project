#include "../Include/Macro_Include.h"
#include "../Include/Item.h"

/* Constructors */
Item::Item() : m_name("NULL"), m_category(ItemCategories::NO_ITEM)
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

Item & Item::operator=(const Item & item)
{
	m_category = item.m_category;
	m_name = m_name;

	return *this;
}

/* Getters */
std::string Item::getName() const
{
	return m_name;
}

ItemCategories Item::getCategory() const
{
	return m_category;
}

/* Category (string not enum [for display]) */
std::string Item::showCategory() const
{
	switch (m_category)
	{
	case ItemCategories::NO_ITEM:
		return "None";
		break;
	case ItemCategories::ARMOR:
		return "Armor";
		break;
	case ItemCategories::PRIMARY_WEAPON:
		return "Primary Weapon";
		break;
	case ItemCategories::SECONDARY_WEAPON:
		return "Secondary Weapon";
		break;
	default:
		return "None";
		break;
	}
}
