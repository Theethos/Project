#ifndef _MACROS_H_
#define _MACROS_H_

/* Macro for display */
#define GENDER(sexe, maleAction, femaleAction) ((sexe == MALE) ? maleAction : femaleAction)
#define PLURAL(x, plural, singular) ((x>1) ? plural : singular)
#define WHICH_WEAPON(x, y, ifX, ifY) ((x>y) ? ifX : ifY)

#endif // !_MACROS_H_
