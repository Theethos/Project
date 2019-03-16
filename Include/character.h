#ifndef CHARACTER_H
#define CHARACTER_H
/*
 *  This header contains the Character Class
 */

#include "inventory.h"
#include "item.h"

#include <string>

 /* Enumeration */

enum Sexe { MALE, FEMALE };
enum HairColor { BLOND, DARK, BROWN, RED, BLUE, GREEN };
enum HairStyle { SHORT, LONG };


/* Structures */

struct LifePoints
{
	int currentLifePoints;
	int levelLifePoints;
	int characteristicLifePoint;
	int equipmentLifePoints;
};
struct Level
{
	int level;
	int currentLevelEXP;
	int nextLevelEXP;
};
struct Hair
{
	HairColor color;
	HairStyle style;
};
 
/* Validate species : Human/Elf/Goblin --- Possible species : Centaur/Ghost/Giant/Trool or Troll/And all hybrid species */
class Character
{
public:
    Character(std::string name = "Mickael", Sexe sexe = MALE , HairColor color = DARK, HairStyle style = SHORT);
    ~Character();

    /* Methods */
	void introduce();
	void gainEXP(int EXPValue);
	void receiveDamage(int DamageValue);
	void hitWithWeapon(Character &target) const;
	//void pickUpItem(Item *item);

	/* Getters */
	std::string getName() const;
	Sexe getSexe() const;
	int getLifePoints() const;
	int getLevel() const;
	Inventory getInventory() const;

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
	Inventory m_inventory;
};

#endif // CHARACTER_H