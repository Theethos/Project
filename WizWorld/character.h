#ifndef CHARACTER_H
#define CHARACTER_H
/*
 *  This header contains the Character Class
 */
#include <iostream>
#include <string>

#include "constants_enumerations.h"

class Character
{
public:
    Character();
    Character(std::string name, Sexe sexe, HairColor color, HairStyle style);
    ~Character();

    /* Methods */
	void introduce();
	void gainEXP(int EXPValue);
	void receiveDamage(int DamageValue);

	/* Getters */
	std::string getName() const;
	Sexe getSexe() const;
	int getLifePoints() const;
	int getLevel() const;

	/* Setters */
	void setName(std::string name);
	void setSexe(Sexe sexe);
	void setHair(HairColor color, HairStyle style);

protected:

    std::string m_name;
    Sexe m_sexe;
	Hair m_hair;
    Level m_level;
    LifePoints m_lifePoints;
};
#endif // CHARACTER_H
