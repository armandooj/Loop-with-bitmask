#ifndef PTHZERO_H
#define PTHZERO_H

#include "loopandbitmask.h"

struct pthzero_data {
  const struct TripletD const * restrict tab;
  const char const * restrict bitmasque;
  int nb;
  struct TripletD somme;
};

extern void pthZero(const struct TripletD const * restrict tab,
		    const char const * restrict bitmasque,
		    int nb, struct TripletD * restrict somme);

#define NBTHREADS (4)

#endif
