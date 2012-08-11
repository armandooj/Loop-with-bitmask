#ifndef CZERO_H
#define CZERO_H

#include "loopandbitmask.h"

void avecRestrictIf(const struct TripletD const * restrict tab,
		    const char const * restrict bitmasque,
		    int nb, struct TripletD * restrict somme);

void avecRestrictZero(const struct TripletD const * restrict tab,
		    const char const * restrict bitmasque,
		      int nb, struct TripletD * restrict somme);



#endif
