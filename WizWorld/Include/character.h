/* Validate species : Human/Elf/Goblin --- Possible species : Centaur/Ghost/Giant/Trool or Troll/And all hybrid species */

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Inventory.h"

/* Avoid mutual inclusions */
class Item;

/* Structures */
struct HealthPoints
{
	long currentHealthPoints;
	// Player gains HP every level
	long levelHealthPoints;
	// HP gained with characteristics
	long characteristicHealthPoint;
	// HP gained with stuff
	long equipmentHealthPoints;
};
struct Level
{
	int level;
	long long currentLevelEXP;
	long long nextLevelEXP;
};
struct Hair
{
	HairColor color;
	HairStyle style;
};
 

class Character
{
public:
	Character();
    Character(std::string name, Sexe sexe, HairColor color, HairStyle style);
	virtual ~Character();

	/* Displays informations about the character (@member[name], @member[level] and @member[healthPoints]) */
	void introduce() const;

	void gainEXP(long long EXPValue);
	void receiveDamage(int damageValue);
	void hitWithWeapon(Character &target) const;
	void pickUpItem(Item *item);
	void equipItem(Item *item);
	void displayInventory() const;

	/* Getters */
	std::string getName() const;
	Sexe getSexe() const;
	int getHealthPoints() const;
	int getLevel() const;
	Inventory* getInventory();

	/* Setters */
	void setName(std::string name);
	void setSexe(Sexe sexe);
	void setHair(HairColor color, HairStyle style);

protected:

    std::string name;
    Sexe sexe;
	Hair hair;
    Level level;
    HealthPoints healthPoints;
	Inventory inventory;	
};

#endif // _CHARACTER_H_