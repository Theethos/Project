#include "../Include/Macro_Include.h"
#include "../Include/Item.h"

/* Constructors */
Item::Item() : name("NULL"), category(ItemCategories::NO_ITEM)
{}

Item::Item(std::string name, ItemCategories category) : name(name), category(category)
{}

Item::Item(const Item & item)
{
	this->category = item.category;
	this->name = item.name;
}

/* Destructor */
Item::~Item()
{}

Item & Item::operator=(const Item & item)
{
	this->category = item.category;
	this->name = name;

	return *this;
}

/* Getters */
std::string Item::getName() const
{
	return this->name;
}

ItemCategories Item::getCategory() const
{
	return this->category;
}

/* Category (string not enum [for display]) */
std::string Item::showCategory() const
{
	switch (this->category)
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
