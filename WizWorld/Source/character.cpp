#include <iostream>
#include <string>

#include "../Include/character.h"
#include "../Include/macros.h"

/*
 * ==================================================
 * ================= Class Character ================
 * ==================================================
 */

/* Constructors */
Character::Character() : m_name("Mickael"), m_sexe(MALE), m_hair{ DARK, SHORT }, m_level{ 1, 0, 300 }, m_lifePoints{ 100, 100, 0, 0 }, m_inventory()
{}

Character::Character(std::string name, Sexe sexe, HairColor color, HairStyle style) : m_name(name), m_sexe(sexe), m_hair{ color, style }, m_level{ 1, 0, 300 }, m_lifePoints{ 100, 100, 0, 0 }, m_inventory()
{}

/* Destructor */
Character::~Character() 
{}

/*=== Methods ===*/

/* Displays informations about the character */
void Character::introduce() const
{
	std::cout << "Hello, my name is " << m_name << ". I am level " << m_level.level << " and I have " << m_lifePoints.currentLifePoints << "/" << m_lifePoints.characteristicLifePoint + m_lifePoints.equipmentLifePoints + m_lifePoints.levelLifePoints << " life points." << std::endl;
}
/* Adds @param[EXPValue] to @member[level] */
void Character::gainEXP(int EXPValue)
{
	m_level.currentLevelEXP += EXPValue;
	if (m_level.currentLevelEXP >= m_level.nextLevelEXP)
	{
		if (m_level.level < 50) // Level max is 50
		{
			m_level.level += 1;
			m_level.nextLevelEXP = (int)(m_level.nextLevelEXP * 1.5); // Each level, characters need 1.5 more EXP to level up
		}
		else // Amount of EXP already at max
		{
			m_level.currentLevelEXP = m_level.nextLevelEXP;
		}
	}
}
/* Remove @param[DamageValue] to @member[lifPoints] */
void Character::receiveDamage(int damageValue)
{
	std::cout << m_name << " loses " << damageValue << " life points." << std::endl;
	m_lifePoints.currentLifePoints -= damageValue;
	if (m_lifePoints.currentLifePoints < 0)
	{
		m_lifePoints.currentLifePoints = 0;
	}
}
/* Attacks @param[target] with the primary weapon */
void Character::hitWithWeapon(Character &target) const
{
	Weapon *weapon = WHICH_WEAPON(m_inventory.getWeapon_1()->getDamage(), m_inventory.getWeapon_2()->getDamage(), m_inventory.getWeapon_1(), m_inventory.getWeapon_2());
	std::cout << m_name << " hits " << target.m_name << " with " << GENDER(m_sexe, "his ", "her ") << weapon->getName() << "." << std::endl;

	target.receiveDamage(weapon->getDamage());
}
/* Puts @param[item] in @member[inventory] if it is not full */
void Character::pickUpItem(Item * item)
{
	m_inventory.setBag(item);
}
/* Equips @param[item] */
void Character::equipItem(Item * item)
{
	m_inventory.equipItem(item);
}

void Character::displayInventory() const
{
	std::cout << "Bag : [ ";
	for (int i = 0; i < m_inventory.getSize(); i++)
	{
		if (m_inventory.getBag()[i])
			std::cout << m_inventory.getBag()[i]->getName() << " ";
		else
			std::cout << "..." << " ";
	}
	std::cout << "]" << std::endl << "      [ ";
	for (int i = 0; i < m_inventory.getSize(); i++)
	{
		if (m_inventory.getBag()[i] != nullptr)
			std::cout << m_inventory.getBag()[i]->showCategory() << " ";
		else
			std::cout << "..." << " ";
	}
	std::cout << "]" << std::endl << std::endl << "Stuff : [ ";
	for (int i = 0; i < (int)RING_2; i++)
	{
		if (m_inventory.getStuff()[i] != nullptr)
			std::cout << m_inventory.getStuff()[i]->getName() << " ";
		else
			std::cout << "..." << " ";
	}
	std::cout << "]" << std::endl << "        [ ";
	for (int i = 0; i < (int)RING_2; i++)
	{
		if (m_inventory.getStuff()[i] != nullptr)
			std::cout << m_inventory.getStuff()[i]->getCategory() << " ";
		else
			std::cout << "..." << " ";
	}
	std::cout << "]" << std::endl << std::endl << "Weapon : - Primary weapon : ";
	if (m_inventory.getWeapon_1() != nullptr)
		std::cout << m_inventory.getWeapon_1()->getName() << " (" << m_inventory.getWeapon_1()->showCategory() << ", " << m_inventory.getWeapon_1()->getDamage() << PLURAL(m_inventory.getWeapon_1()->getDamage(), " damages)", " damage)") << std::endl;
	else
		std::cout << " None" << std::endl;
	if (m_inventory.getWeapon_2() != nullptr)
		std::cout << "         - Secondary weapon : " << m_inventory.getWeapon_2()->getName() << " (" << m_inventory.getWeapon_2()->showCategory() << ", " << m_inventory.getWeapon_2()->getDamage() << PLURAL(m_inventory.getWeapon_2()->getDamage(), " damages)", " damage)") << std::endl << std::endl;
	else
		std::cout << " None" << std::endl << std::endl;
}

/*=== Getters ===*/

/* Name */
std::string Character::getName() const
{
	std::cout << "Your character is called " << m_name << std::endl;
	return m_name;
}
/* Sexe */
Sexe Character::getSexe() const
{
	std::cout << m_name << " is a ";
	std::cout << GENDER(m_sexe, "man ", "woman ") << std::endl;
	return m_sexe;
}
/* LifePoints*/
int Character::getLifePoints() const
{
	std::cout << m_name << " has " << m_lifePoints.currentLifePoints << "/" << m_lifePoints.characteristicLifePoint + m_lifePoints.equipmentLifePoints + m_lifePoints.levelLifePoints << " life points." << std::endl;
	return m_lifePoints.currentLifePoints;
}
/* Level */
int Character::getLevel() const
{
	std::cout << m_name << " is level " << m_level.level << ". ";
	std::cout << GENDER(m_sexe, "his", "her") << "experience is " << m_level.currentLevelEXP << "/" << m_level.nextLevelEXP << std::endl;
	return m_level.level;
}

/* Inventory */
Inventory Character::getInventory() const
{
	return m_inventory;
}

/*=== Setters ===*/

/* Name*/
void Character::setName(std::string name)
{
	std::cout << m_name << " will be called " << name << " from now." << std::endl;
	m_name = name;
}
/* Sexe */
void Character::setSexe(Sexe sexe)
{
	std::cout << m_name << " is now a ";
	std::cout << GENDER(m_sexe, "man ", "woman ") << std::endl;
	m_sexe = sexe;
}
/* Hair */
void Character::setHair(HairColor color, HairStyle style)
{
	m_hair.color = color;
	m_hair.style = style;
}
