#include "Include/Macros_Includes.h"

#include "Include/Character.h"
#include "Include/Inventory.h"
#include "Include/Item.h"
#include "Include/Weapon.h"

int main()
{
    std::cout << "\n=== Beginning ===\n" << std::endl;

	Character mickael = Character();
	Character ahbdekha = Character("Ahbdekha", MALE, DARK, LONG);

	mickael.introduce();
	ahbdekha.introduce();

	Weapon wand("Shiny Wand", PRIMARY_WEAPON, WAND, 30);

	ahbdekha.displayInventory();

	ahbdekha.pickUpItem(&wand);

	ahbdekha.displayInventory();

	ahbdekha.getInventory()->equipItem(ahbdekha.getInventory()->getBag()[0]);

	ahbdekha.displayInventory();

	ahbdekha.hitWithWeapon(mickael);
	mickael.getLifePoints();
	std::cout << std::endl;
	
	std::cout << "\n=== End ===\n" << std::endl;
    
	system("PAUSE");
	return 0;
}
