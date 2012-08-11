#include "czero.h"

void avecRestrictIf(const struct TripletD const * restrict tab,
		    const char const * restrict bitmasque,
		    int nb, struct TripletD * restrict somme) {
  for(int i=0; i < nb; i++) {
    if (bitmasque[i]) {
      somme->valeurs[0] += tab[i].valeurs[0]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
    }
  } 
}

void avecRestrictZero(const struct TripletD const * restrict tab,
		    const char const * restrict bitmasque,
		    int nb, struct TripletD * restrict somme) {
  for(int i=0; i < nb; i++) {
      somme->valeurs[0] += bitmasque[i] * tab[i].valeurs[0]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
  } 
}
