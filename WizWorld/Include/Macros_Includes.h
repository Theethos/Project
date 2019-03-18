#ifndef _MACROS_INCLUDES_H_
#define _MACROS_INCLUDES_H_

/*
 * ==================================================
 * ================== Includes ======================
 * ==================================================
 */

#include <iostream>
#include <string>

/*
 * ==================================================
 * =================== Macros =======================
 * ==================================================
 */

#define GENDER(sexe, maleAction, femaleAction) ((sexe == MALE) ? maleAction : femaleAction)
#define PLURAL(x, plural, singular) ((x>1) ? plural : singular)
#define WHICH_WEAPON(x, y, ifX, ifY) ((x>y) ? ifX : ifY)

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

#endif // !_MACROS_INCLUDES_H_
