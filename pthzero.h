#ifndef PTHZERO_H
#define PTHZERO_H

struct pthzero_data {
  const struct TripletD const * restrict tab;
  const char const * restrict bitmasque;
  int nb, struct TripletD somme;
};

#define NBTHREADS (2)

#endif
