#ifndef CFORTRAN_H
#define CFORTRAN_H

void fortranzero_ (const struct TripletD const * restrict tab,
		   const char const * restrict bitmasque,
		   int *nb, double *somme);
void fortranif_ (const struct TripletD const * restrict tab,
		 const char const * restrict bitmasque,
		 int *nb, double *somme);


#endif
