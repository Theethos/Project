#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/Item.h"
#include "../Include/Weapon.h"

/* Constructors */
Weapon::Weapon() : Item(), weaponCategory(WeaponCategories::NO_WEAPON), damage(0)
{}

Weapon::Weapon(std::string name, ItemCategories category, WeaponCategories weaponCategory, int damage) : Item(name, category), weaponCategory(weaponCategory), damage(damage)
{}

Weapon::Weapon(const Weapon & weapon)
{
	this->category = weapon.category;
	this->name = weapon.name;
	this->damage = weapon.damage;
	this->weaponCategory = weapon.weaponCategory;
}

/* Destructors */
Weapon:: ~Weapon()
{}

Weapon & Weapon::operator=(const Weapon &weapon)
{
	this->category = weapon.category;
	this->name = weapon.name;
	this->damage = weapon.damage;
	this->weaponCategory = weapon.weaponCategory;

	return *this;
}

/* Getters */
int Weapon::getDamage() const
{
	return this->damage;
}

WeaponCategories Weapon::getWeaponCategory() const
{
	return this->weaponCategory;
}

/* WeaponCategory (string not enum [for display]) */
std::string Weapon::showCategory() const
{
	switch (this->weaponCategory)
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