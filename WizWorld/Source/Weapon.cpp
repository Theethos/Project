#include "../Include/Macro_Include.h"
#include "../Include/Item.h" // Mother class
#include "../Include/Weapon.h"

/* Constructors */
Weapon::Weapon() : Item(), m_weaponCategory(WeaponCategories::NO_WEAPON), m_damage(0)
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

Weapon & Weapon::operator=(const Weapon &weapon)
{
	m_category = weapon.m_category;
	m_name = weapon.m_name;
	m_damage = weapon.m_damage;
	m_weaponCategory = weapon.m_weaponCategory;

	return *this;
}

/* Getters */
int Weapon::getDamage() const
{
	return m_damage;
}

WeaponCategories Weapon::getWeaponCategory() const
{
	return m_weaponCategory;
}

/* WeaponCategory (string not enum [for display]) */
std::string Weapon::showCategory() const
{
	switch (m_weaponCategory)
	{
	case WeaponCategories::NO_WEAPON:
		return "None";
		break;
	case WeaponCategories::WAND:
		return "Wand";
		break;
	case WeaponCategories::STAFF:
		return "Staff";
		break;
	case WeaponCategories::MAGIC_RING:
		return "Magic ring";
		break;
	case WeaponCategories::SHIELD:
		return "Shield";
		break;
	default:
		return "None";
		break;
	};
}