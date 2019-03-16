#include "../Include/item.h"

using namespace std;
/*
 * Class 'Item'
 */

Item::Item() : m_name("NULL"), m_category(NO_ITEM)
{}
Item::Item(string name, ItemCategories category) : m_name(name), m_category(category)
{}
Item::Item(const Item & item)
{
	m_category = item.m_category;
	m_name = item.m_name;
}
Item::~Item()
{}
Item & Item::operator=(const Item & item)
{
	m_category = item.m_category;
	m_name = m_name;

	return *this;
}
string Item::getName() const
{
	return m_name;
}
ItemCategories Item::getCategory() const
{
	return m_category;
}

/*
 * Class 'Weapon'
 */

Weapon::Weapon() : Item("Punch", NO_ITEM), m_damage(10)
{}
Weapon::Weapon(string name, ItemCategories category, int damage) : Item(name, category), m_damage(damage)
{}
Weapon::Weapon(const Weapon & weapon)
{
	m_category = weapon.m_category;
	m_name = weapon.m_name;
	m_damage = weapon.m_damage;
}
Weapon:: ~Weapon()
{}
Weapon & Weapon::operator=(const Weapon &weapon)
{
	m_category = weapon.m_category;
	m_name = weapon.m_name;
	m_damage = weapon.m_damage;

	return *this;
}
int Weapon::getDamage() const
{
	return m_damage;
}
