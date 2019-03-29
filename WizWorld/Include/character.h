/* Validate species : Human/Elf/Goblin --- Possible species : Centaur/Ghost/Giant/Trool or Troll/And all hybrid species */

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Inventory.h"

/*=== Avoid mutual inclusions ===*/
class Item;

/*=== Structures ===*/

struct HealthPoints
{
	long currentHealthPoints;
	long levelHealthPoints;
	long characteristicHealthPoint;
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
 
/*
 * ==================================================
 * ================= Class Character ================
 * ==================================================
 */
class Character
{
public:
	/*=== Constructors/Destructor ===*/

	Character();
    Character(std::string name, Sexe sexe, HairColor color, HairStyle style);
	virtual ~Character();
	//gne
    /*=== Methods ===*/

	/* Displays informations about the character (@member[name], @member[level] and @member[healthPoints]) */
	void introduce() const;
	/* Adds @param[EXPValue] to @member[level] */
	void gainEXP(long long EXPValue);
	/* Remove @param[damageValue] to @member[lifPoints] */
	void receiveDamage(int damageValue);
	/* Attacks @param[target] with the primary weapon */
	void hitWithWeapon(Character &target) const;
	/* Puts @param[item] in @member[inventory] if it is not full */
	void pickUpItem(Item *item);
	/* Equips @param[item] */
	void equipItem(Item *item);
	/* Displays all items equiped and carryed by the character */
	void displayInventory() const;

	/*=== Getters ===*/

	/* Name */
	std::string getName() const;
	/* Sexe */
	Sexe getSexe() const;
	/* HealthPoints*/
	int getHealthPoints() const;
	/* Level */
	int getLevel() const;
	/* Inventory */
	Inventory* getInventory();

	/*=== Setters ===*/
	
	/* Name*/
	void setName(std::string name);
	/* Sexe */
	void setSexe(Sexe sexe);
	/* Hair */
	void setHair(HairColor color, HairStyle style);

protected:

    std::string m_name;
    Sexe m_sexe;
	Hair m_hair;
    Level m_level;
    HealthPoints m_healthPoints;
	Inventory m_inventory;	
};

#endif // _CHARACTER_H_