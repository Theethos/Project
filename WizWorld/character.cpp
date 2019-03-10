#include "../include/character.h"

using namespace std;

/*
 *  Class 'Character'
 */

Character::Character() : m_name("A character has no name"), m_sexe(MALE), m_hair{ DARK, SHORT }, m_level{ 1, 0, 300 }, m_lifePoints{ 100, 100, 0, 0 } {}

Character::Character(string name, Sexe sexe, HairColor color, HairStyle style) : m_name(name), m_sexe(sexe), m_hair{ color, style }, m_level{ 1, 0, 300 }, m_lifePoints{ 100, 100, 0, 0 } {}

Character::~Character() {}

/* Methods */
void Character::introduce()
{
	cout << "Hello, my name is " << m_name << ". I am level " << m_level.level << " and I have " << m_lifePoints.currentLifePoints << "/" << m_lifePoints.characteristicLifePoint + m_lifePoints.equipmentLifePoints + m_lifePoints.levelLifePoints << " life points." << endl;
}
void Character::gainEXP(int EXPValue)
{
	m_level.currentLevelEXP += EXPValue;
	if (m_level.currentLevelEXP >= m_level.nextLevelEXP)
	{
		// Level max is 50
		if (m_level.level < 50)
		{
			m_level.level += 1;
			// Each level, players need 1.5 more EXP to level up
			m_level.nextLevelEXP = (int)(m_level.nextLevelEXP * 1.5);
		}
		else
		{
			// Amount of EXP already at max
			m_level.currentLevelEXP = m_level.nextLevelEXP;
		}
	}
}
void Character::receiveDamage(int DamageValue)
{
	m_lifePoints.currentLifePoints -= DamageValue;
	if (m_lifePoints.currentLifePoints < 0)
	{
		m_lifePoints.currentLifePoints = 0;
	}
}

/* Getters */
string Character::getName() const
{
	cout << "Your character is called " << m_name << endl;
	return m_name;
}
Sexe Character::getSexe() const
{
	cout << m_name << " is a ";
	cout << ((m_sexe == MALE) ? "man " : "woman") << endl;
	return m_sexe;
}
int Character::getLifePoints() const
{
	cout << m_name << " has " << m_lifePoints.currentLifePoints << "/" << m_lifePoints.characteristicLifePoint + m_lifePoints.equipmentLifePoints + m_lifePoints.levelLifePoints << " life points." << endl;
	return m_lifePoints.currentLifePoints;
}
int Character::getLevel() const
{
	cout << m_name << " is level " << m_level.level << ". ";
	cout << ((m_sexe == MALE) ? "His " : "Her ") << "experience is " << m_level.currentLevelEXP << "/" << m_level.nextLevelEXP << endl;
	return m_level.level;
}

/* Setters */
void Character::setName(string name)
{
	cout << m_name << " will be called " << name << " from now." << endl;
	m_name = name;
}
void Character::setSexe(Sexe sexe)
{
	cout << m_name << " is now a ";
	cout << ((m_sexe == MALE) ? "man " : "woman") << endl;
	m_sexe = sexe;
}
void Character::setHair(HairColor color, HairStyle style)
{
	m_hair.color = color;
	m_hair.style = style;
}