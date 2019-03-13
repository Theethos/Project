#include <iostream>

#include "Include/character.h"
#include "Include/constants_enumerations.h"

using namespace std;

int main()
{
    cout << "\n=== Beginning ===\n" << endl;


	Character mickael;
	Character ahbdekha("Ahbdekha", MALE, DARK, LONG);

	mickael.introduce();
	ahbdekha.introduce();

	mickael.hitWithWeapon(ahbdekha);
	ahbdekha.getLifePoints();

    cout << "\n=== End ===\n" << endl;
	cout << "\n=== Press 'enter' to end the program ===\n" << endl;
	getchar();
    return 0;
}
