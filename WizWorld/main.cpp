#include <iostream>

#include "Include/character.h"
#include "Include/constants_enumerations.h"

using namespace std;

int main()
{
    cout << "\n=== Debut ===\n" << endl;

	Character gordon("Gordon", MALE, DARK, SHORT);
	Character ahbdekha("Ahbdekha", MALE, DARK, LONG);

	gordon.introduce();
	ahbdekha.introduce();

	gordon.hitWithWeapon(ahbdekha);
	ahbdekha.getLifePoints();

    cout << "\n=== Fin ===\n" << endl;
    return 0;
}
