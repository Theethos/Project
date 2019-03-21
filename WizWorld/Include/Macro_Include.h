#ifndef _MACROS_INCLUDES_H_
#define _MACROS_INCLUDES_H_

/*
 * ==================================================
 * ================== Includes ======================
 * ==================================================
 */

#include <iostream>
#include <fstream>
#include <string>

#ifdef _REQUIRE_SFML_
	#include "SFML/Graphics.hpp"
	#include "SFML/Window.hpp"
#endif // _REQUIRE_SFML_


/*
 * ==================================================
 * =================== Macros =======================
 * ==================================================
 */

#define GENDER(sexe, maleAction, femaleAction) ((sexe == MALE) ? maleAction : femaleAction)
#define PLURAL(x, plural, singular) ((x>1) ? plural : singular)
#define MIN(x, y, ifX, ifY) ((x<y) ? ifX : ifY)
#define MAX(x, y, ifX, ifY) ((x>y) ? ifX : ifY)

/*
 * ==================================================
 * ================== Templates =====================
 * ==================================================
 */

template<typename T>
void SWAP_POINTERS(T* x, T* y)
{
	T *tmp = x;
	x = y;
	y = tmp;
}
template<typename T>
void SWAP_VALUE(T* x, T* y)
{
	T tmp = *x;
	*x = *y;
	*y = tmp;
}

/*
 * ==================================================
 * ================= Enumeration ====================
 * ==================================================
 */

enum ItemCategories { NO_ITEM, ARMOR, PRIMARY_WEAPON, SECONDARY_WEAPON };
enum WeaponCategories { NO_WEAPON, WAND, STAFF, MAGIC_RING, SHIELD };
enum ArmorCategories { HAT, CLOAK, CHEST, BELT, PANTS, BOOTS, GLOVE_1, GLOVE_2, NECKLESS, EARING_1, EARING_2, RING_1, RING_2, NO_ARMOR };
enum Sexe { MALE, FEMALE };
enum HairColor { BLOND, DARK, BROWN, RED, BLUE, GREEN };
enum HairStyle { SHORT, LONG };

#endif // !_MACROS_INCLUDES_H_
