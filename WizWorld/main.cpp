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

	char fin = 0;
	cout << "\n=== Press any key + 'enter' to end the program" << endl;
	cin >> fin;
    cout << "\n=== End ===\n" << endl;
    return 0;
}
