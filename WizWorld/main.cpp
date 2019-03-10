#include <iostream>

#include "include/character.h"
#include "include/constants_enumerations.h"

using namespace std;

int main()
{
    cout << "Debut" << endl;
	Character gordon("Gordon", MALE, DARK, SHORT);
	gordon.introduce();
	gordon.getLevel();
	gordon.getLifePoints();
    cout << "Fin" << endl;
    return 0;
}
