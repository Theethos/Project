#include "Include/Macros_Includes.h"

#include "Include/Character.h"
#include "Include/Inventory.h"
#include "Include/Item.h"
#include "Include/Weapon.h"
#include "Include/Armor.h"

int main()
{
    std::cout << "\n=== Beginning ===\n" << std::endl;

	Character mickael = Character();
	Character ahbdekha = Character("Ahbdekha", MALE, DARK, LONG);

	mickael.introduce();
	ahbdekha.introduce();

	std::cout << std::endl;
	std::cout << "=================" << std::endl << std::endl;

	Weapon wand("Shiny wand", PRIMARY_WEAPON, WAND, 30);
	Weapon shield("Mighty shield", SECONDARY_WEAPON, SHIELD, 10);
	Armor chest("Bright chest", ARMOR, CHEST);
	Armor helmet("Coconut helmet", ARMOR, HAT);
	
	ahbdekha.displayInventory();
	std::cout << "=================" << std::endl << std::endl;


	ahbdekha.pickUpItem(&wand);
	ahbdekha.pickUpItem(&shield);
	ahbdekha.pickUpItem(&chest);
	ahbdekha.pickUpItem(&helmet);
	std::cout << std::endl << "=================" << std::endl << std::endl;

	ahbdekha.displayInventory();
	std::cout << "=================" << std::endl << std::endl;

	ahbdekha.equipItem(&wand);
	ahbdekha.equipItem(&shield);
	ahbdekha.equipItem(&chest);
	ahbdekha.equipItem(&helmet);
	std::cout << std::endl << "=================" << std::endl << std::endl;

	ahbdekha.displayInventory();
	std::cout << "=================" << std::endl << std::endl;


	ahbdekha.hitWithWeapon(mickael);
	mickael.getHealthPoints();
	std::cout << "=================" << std::endl << std::endl;

	mickael.gainEXP(5148376331); // 5 148 376 331 max EXP;
	std::cout << std::endl << "=================" << std::endl << std::endl;

	std::cout << std::endl;
	std::cout << "\n=== End ===\n" << std::endl;
    
	system("PAUSE");
	return 0;
}
