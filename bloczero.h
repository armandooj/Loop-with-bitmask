#ifndef BLOCZERO_H
#define BLOCZERO_H

#include "loopandbitmask.h"

void avecRestrictBlocZeroF(const float const * restrict tab,
			  const char const * restrict bitmasque,
			  int nb, struct TripletD * restrict somme);

void avecRestrictBlocVectorZeroF(const float const * restrict tab,
				 const float const * restrict bitmasque,
				 int nb, struct TripletD * restrict somme);

#endif
