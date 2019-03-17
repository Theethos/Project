/* Validate species : Human/Elf/Goblin --- Possible species : Centaur/Ghost/Giant/Trool or Troll/And all hybrid species */

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Inventory.h"
#include "Item.h"

 /*=== Enumerations ===*/

enum Sexe { MALE, FEMALE };
enum HairColor { BLOND, DARK, BROWN, RED, BLUE, GREEN };
enum HairStyle { SHORT, LONG };

/*=== Structures ===*/

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

	/* Displays informations about the character (@member[name], @member[level] and @member[lifePoints]) */
	void introduce() const;
	/* Adds @param[EXPValue] to @member[level] */
	void gainEXP(int EXPValue);
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
	/* LifePoints*/
	int getLifePoints() const;
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
    LifePoints m_lifePoints;
	Inventory m_inventory;	
};

#endif // _CHARACTER_H_