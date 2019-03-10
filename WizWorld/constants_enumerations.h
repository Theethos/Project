#ifndef CONSTANTS_ENUMERATIONS_H
#define CONSTANTS_ENUMERATIONS_H

/* Validate species : Human/Elf/Goblin --- Possible species : Centaur/Ghost/Giant/Trool or Troll/And all hybrid species */
/* Validate weapons : Wand/Staff/Ring  --- Possible weapons : Bow/Sword/Hammer/Axe/Club */
/*									   --- Possible equipments : Hat/Chest/Belt/Pants/Boots/Gloves/Clock/Weapon/Shield */


// Related to Character Class
enum Sexe {MALE, FEMALE};
enum HairColor {BLOND, DARK, BROWN, RED, BLUE, GREEN};
enum HairStyle {SHORT, LONG};


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

#endif // CONSTANTS_ENUMERATIONS_H
