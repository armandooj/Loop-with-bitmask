#include "bloczero.h"

void avecRestrictBlocZeroF(const float const * restrict tab,
			   const char const * restrict bitmasque,
			   int nb, struct TripletD * restrict somme) {

  float localsom = 0.0;
  for(int i=0; i < nb; i++) {
       localsom += bitmasque[i] * tab[i]; 
  } 
  somme->valeurs[0] = localsom;
}


typedef float v4f __attribute__ ((vector_size (16)));

void avecRestrictBlocVectorZeroF(const float const * restrict tab,
				 const float const * restrict bitmasque,
				 int nb, struct TripletD * restrict somme) {

  const v4f *a = (v4f *) tab;
  const v4f *bit = (v4f *) bitmasque;
  v4f vsomme;

  for(int i=0; i < nb/4; i++) {
      vsomme += bit[i] * a[i]; 
  } 
  
  float *val4 = (float *) & vsomme;
  for(int i=0; i < 4; i++)
    somme->valeurs[0] += val4[i];

}
