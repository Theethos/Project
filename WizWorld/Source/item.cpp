#include <string>

#include "../Include/item.h"
#include "../Include/inventory.h"

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
	return this->m_name;
}
/* Category */
ItemCategories Item::getCategory() const
{
	return this->m_category;
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

/*
 * ==================================================
 * ================ Class Weapon ====================
 * ==================================================
 */

/* Constructors */
Weapon::Weapon() : Item(), m_weaponCategory(NO_WEAPON), m_damage(0)
{}
Weapon::Weapon(std::string name, ItemCategories category, WeaponCategories weaponCategory, int damage) : Item(name, category), m_weaponCategory(weaponCategory), m_damage(damage)
{}
Weapon::Weapon(const Weapon & weapon)
{
	m_category = weapon.m_category;
	m_name = weapon.m_name;
	m_damage = weapon.m_damage;
	m_weaponCategory = weapon.m_weaponCategory;
}
/* Destructors */
Weapon:: ~Weapon()
{}

/*=== Operator overload ===*/

Weapon & Weapon::operator=(const Weapon &weapon)
{
	m_category = weapon.m_category;
	m_name = weapon.m_name;
	m_damage = weapon.m_damage;
	m_weaponCategory = weapon.m_weaponCategory;

	return *this;
}

void Weapon::equips(Inventory *inventory)
{
	if (this->m_category == PRIMARY_WEAPON)
		inventory->setWeapon_1(this);
	else // SECONDARY_WEAPON
		inventory->setWeapon_2(this);
}

/*=== Getters ===*/

/* Damage */
int Weapon::getDamage() const
{
	return m_damage;
}

std::string Weapon::showCategory() const
{
	switch (m_weaponCategory)
	{
	case NO_WEAPON:
		return "None";
		break;
	case WAND:
		return "Wand";
		break;
	case STAFF:
		return "Staff";
		break;
	case MAGIC_RING:
		return "Magic ring";
		break;
	case SHIELD:
		return "Shield";
		break;
	default:
		return "None";
		break;
	};
}
