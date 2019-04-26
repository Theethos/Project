#include "Precompiled_Header.h"
/* 
#include "../Include/Macros.h"
#include "../Include/Character.h"

// Constructors
Character::Character() : name("Mickael"), sexe(Sexe::MALE), hair{ HairColor::DARK, HairStyle::SHORT }, level{ 1, 0, 300 }, healthPoints{ 100, 100, 0, 0 }, inventory()
{}

Character::Character(std::string name, Sexe sexe, HairColor color, HairStyle style)
					: name(name), sexe(sexe), hair{ color, style }, level{ 1, 0, 300 }, 
					  healthPoints{ 100, 100, 0, 0 }, inventory()
{}

// Destructor 
Character::~Character() 
{}

// Displays informations about the character
void Character::introduce() const
{
	std::cout << "Hello, my name is " << this->name << ". I am level " << this->level.level << " and I have " << this->healthPoints.currentHealthPoints << "/" << this->healthPoints.characteristicHealthPoint + this->healthPoints.equipmentHealthPoints + this->healthPoints.levelHealthPoints << " health points." << std::endl;
}

// Adds EXPValue to the character's current EXP
void Character::gainEXP(long long EXPValue)
{
	std::cout << this->name << " gains " << std::to_string(EXPValue) << " EXP! " << GENDER(this->sexe, "His", "Her") << " current EXP : " << this->level.currentLevelEXP << "/" << this->level.nextLevelEXP << "." << std::endl << std::endl;
	
	this->level.currentLevelEXP += EXPValue;
	while (this->level.currentLevelEXP >= this->level.nextLevelEXP)
	{
		if (this->level.level < 50) // Level max is 50 (== 5 148 376 331 EXP)
		{
			this->level.level += 1;
			
			std::cout << this->name << " levels up ! " << GENDER(this->sexe, "He", "She") << " is now level " << this->level.level;
			
			// Each level, characters need 0.405 more EXP to level up
			this->level.nextLevelEXP += (long long)(this->level.nextLevelEXP * 0.405); 
			// Each level, characters gain 50 "native" HP
			this->healthPoints.levelHealthPoints += 50; 
			
			std::cout << " (" << MIN(this->level.currentLevelEXP, this->level.nextLevelEXP, this->level.currentLevelEXP, this->level.nextLevelEXP) << "/" << this->level.nextLevelEXP << ")" << std::endl;
		}
		// Amount of EXP already at max
		else 
		{
			std::cout << this->name << " is already level " << this->level.level;
			
			this->level.currentLevelEXP = this->level.nextLevelEXP;
			
			std::cout << " (" << this->level.currentLevelEXP << "/" << this->level.nextLevelEXP << ")" << std::endl;
			// Goes out the while loop
			break;
		}
	}
}

// Removes DamageValue to the character's health points 
void Character::receiveDamage(int damageValue)
{
	std::cout << this->name << " loses " << damageValue << " health points." << std::endl;
	
	this->healthPoints.currentHealthPoints -= damageValue;
	// Check that HPs dont go below 0
	if (this->healthPoints.currentHealthPoints < 0)
	{
		this->healthPoints.currentHealthPoints = 0;
	}
}

// Attacks the target with the weapon that has the higher damages 
void Character::hitWithWeapon(Character &target) const
{
	// Select the best weapon 
	Weapon *weapon = MAX(this->inventory.getWeapon_1()->getDamage(), this->inventory.getWeapon_2()->getDamage(), this->inventory.getWeapon_1(), this->inventory.getWeapon_2());
	std::cout << this->name << " hits " << target.name << " with " << GENDER(this->sexe, "his ", "her ") << weapon->getName() << "." << std::endl;

	target.receiveDamage(weapon->getDamage());
}

// Puts an item in the character's inventory if it is not full 
void Character::pickUpItem(Item * item)
{
	std::cout << this->name << " picks up \"" << item->getName() << "\"." << std::endl;
	
	this->inventory.setBag(item);
}

// Equips an item depending on its category 
void Character::equipItem(Item * item)
{
	std::cout << this->name << " equips \"" << item->getName() << "\"." << std::endl;
	
	if (item->getCategory() == ItemCategories::PRIMARY_WEAPON)
		this->inventory.setWeapon_1(dynamic_cast<Weapon*>(item));
	else if (item->getCategory() == ItemCategories::SECONDARY_WEAPON)
		this->inventory.setWeapon_2(dynamic_cast<Weapon*>(item));
	else
		this->inventory.setStuff(dynamic_cast<Armor*>(item));
}

// DEBUG FUNCTION : just display what is inside the character's inventory 
void Character::displayInventory() const
{
	std::cout << this->name << "'s inventory : " << std::endl << std::endl << "Bag : [";

	// Display items in bag 
	for (int i = 0; i < this->inventory.getSize(); i++)
	{
		if (this->inventory.getBag()[i])
			std::cout << this->inventory.getBag()[i]->getName() << "//";
		else
			std::cout << "..." << "//";
	}

	std::cout << "]" << std::endl << "      [";

	// Display the item's category
	for (int i = 0; i < this->inventory.getSize(); i++)
	{
		if (this->inventory.getBag()[i] != nullptr)
		{
			std::cout << this->inventory.getBag()[i]->showCategory();

			for (int j = 0; j < this->inventory.getBag()[i]->getName().size() - this->inventory.getBag()[i]->showCategory().size(); j++)
			{
				std::cout << " ";
			}
			std::cout << "//";
		}
		else
			std::cout << "..." << "//";
	}

	std::cout << "]" << std::endl << std::endl << "Stuff : [";
	
	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		if (this->inventory.getStuff()[i] != nullptr)
			std::cout << this->inventory.getStuff()[i]->getName() << "//";
		else
			std::cout << "..." << "//";
	}
	std::cout << "]" << std::endl << "        [";
	for (int i = 0; i < static_cast<int>(ArmorCategories::RING_2); i++)
	{
		if (this->inventory.getStuff()[i] != nullptr)
		{
			std::cout << this->inventory.getStuff()[i]->showCategory();
			for (int j = 0; j < this->inventory.getStuff()[i]->getName().size() - this->inventory.getStuff()[i]->showCategory().size(); j++)
			{
				std::cout << " ";
			}
			std::cout << "//";
		}
		else
			std::cout << "..." << "//";
	}
	std::cout << "]" << std::endl << std::endl << "Weapon : - Primary weapon : ";
	if (this->inventory.getWeapon_1() != nullptr)
		std::cout << this->inventory.getWeapon_1()->getName() << " (" << this->inventory.getWeapon_1()->showCategory() << ", " << this->inventory.getWeapon_1()->getDamage() << PLURAL(this->inventory.getWeapon_1()->getDamage(), " damages)", " damage)") << std::endl;
	else
		std::cout << " None" << std::endl;
	if (this->inventory.getWeapon_2() != nullptr)
		std::cout << "         - Secondary weapon : " << this->inventory.getWeapon_2()->getName() << " (" << this->inventory.getWeapon_2()->showCategory() << ", " << this->inventory.getWeapon_2()->getDamage() << PLURAL(this->inventory.getWeapon_2()->getDamage(), " damages)", " damage)") << std::endl << std::endl;
	else
		std::cout << " None" << std::endl << std::endl;
}

std::string Character::getName() const
{
	std::cout << "Your character is called " << this->name << std::endl;
	return this->name;
}

Sexe Character::getSexe() const
{
	std::cout << this->name << " is a ";
	std::cout << GENDER(this->sexe, "man ", "woman ") << std::endl;
	return this->sexe;
}

int Character::getHealthPoints() const
{
	std::cout << this->name << " has " << this->healthPoints.currentHealthPoints << "/" << this->healthPoints.characteristicHealthPoint + this->healthPoints.equipmentHealthPoints + this->healthPoints.levelHealthPoints << " health points." << std::endl;
	return this->healthPoints.currentHealthPoints;
}

int Character::getLevel() const
{
	std::cout << this->name << " is level " << this->level.level << ". ";
	std::cout << GENDER(this->sexe, "his", "her") << "experience is " << this->level.currentLevelEXP << "/" << this->level.nextLevelEXP << std::endl;
	return this->level.level;
}

Inventory* Character::getInventory()
{
	return &(this->inventory);
}

void Character::setName(std::string name)
{
	std::cout << this->name << " will be called " << name << " from now." << std::endl;
	this->name = name;
}

void Character::setSexe(Sexe sexe)
{
	std::cout << this->name << " is now a ";
	std::cout << GENDER(this->sexe, "man ", "woman ") << std::endl;
	this->sexe = sexe;
}

void Character::setHair(HairColor color, HairStyle style)
{
	this->hair.color = color;
	this->hair.style = style;
}
*/