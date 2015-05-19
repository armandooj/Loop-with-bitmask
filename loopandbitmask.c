//#include <bool.h>
#include <time.h>
#include "loopandbitmask.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "czero.h"
#include "cfortran.h"
#include "pthzero.h"
#include "bloczero.h"

#include "getCPUTime.c"

char *bitmasque;
struct TripletD *tableau;


double diffTemps(struct timespec fin, struct timespec debut) {
  return 1.0*(fin.tv_sec - debut.tv_sec)+1E-9*(fin.tv_nsec - debut.tv_nsec);
}

/*
void afficheTemps(const char *nom, struct TripletD somme,
		  int nb, struct timespec fin, struct timespec debut) {
  double temps = diffTemps(fin, debut);
  printf("%s: %le; temps %le, acc/s %le\n",
	 nom, somme.valeurs[0]+somme.valeurs[1]+somme.valeurs[2],
	 temps,
	 nb / temps);
}
*/

void afficheTemps(const char *nom, struct TripletD somme, int nb, double fin, double debut) {
  // double temps = diffTemps(fin, debut);
  double temps = fin - debut;
  printf("%s: %le; temps %le, acc/s %le\n", nom, somme.valeurs[0] + somme.valeurs[1] + somme.valeurs[2], 
    temps, nb / temps);
}



int main(int argc, char **argv)
{
  assert(argc == 2);
  int nb = atoi(argv[1] );
  //struct timespec debut, milieu, fin;
  double debut, milieu, fin;
  struct TripletD somme = {};

  bitmasque = malloc(sizeof(char) * nb);
  tableau = malloc(sizeof(struct TripletD) * nb);
  
  for(int i=0; i < nb; i++) {
    bitmasque[i] = (drand48() < 0.5) ? 1 : 0;
    for(int j=0; j < 3; j++) {
      tableau[i].valeurs[j] = drand48();
    }
  }

  debut = getCPUTime();
  for(int i=0; i < nb; i++) {
    somme.valeurs[0] += tableau[i].valeurs[0]; 
    //somme.valeurs[1] += tableau[i].valeurs[1]; 
    //somme.valeurs[2] += tableau[i].valeurs[2];
  }
  fin = getCPUTime();
  afficheTemps("SansBitmask", somme, nb, fin, debut);

  struct TripletD zero = {};
  somme = zero;
  debut = getCPUTime();
  for(int i=0; i < nb; i++) {
    if (bitmasque[i]) {
      somme.valeurs[0] += tableau[i].valeurs[0]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
    }
  } 
  fin = getCPUTime();
  afficheTemps("avecIf", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  for(int i=0; i < nb; i+=4) {

      double a = tableau[i].valeurs[0]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
    
      double b = tableau[i+1].valeurs[0]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];

      double c = tableau[i+2].valeurs[0]; 

      double d = tableau[i+3].valeurs[0]; 
	
      if (bitmasque[i])	somme.valeurs[0] += a;
      if (bitmasque[i+1]) somme.valeurs[0] += b;
      if (bitmasque[i+2]) somme.valeurs[0] += c;
      if (bitmasque[i+3]) somme.valeurs[0] += d;
  } 
  fin = getCPUTime();
  afficheTemps("deroule4", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  double *dense = malloc(sizeof(double) * nb);
  int pos;
  for(int i=0;i<nb;i++) {
    if (bitmasque[i]) {
      dense[pos] = tableau[i].valeurs[0];
      pos ++;
    }
  }

  milieu = getCPUTime();
  for(int i=0; i < pos; i++) {
      somme.valeurs[0] += dense[i]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
  } 
  fin = getCPUTime();
  afficheTemps("CopyDense", somme, nb, fin, debut);
  afficheTemps("Dense", somme, nb, fin, milieu);

  somme = zero;
  debut = getCPUTime();
  for(int i=0; i < nb; i++) {
    somme.valeurs[0] += bitmasque[i] * tableau[i].valeurs[0]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
  } 
  fin = getCPUTime();
  afficheTemps("MultiplicationParZero", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  avecRestrictIf(tableau, bitmasque, nb, &somme);
  fin = getCPUTime();
  afficheTemps("FonctionAvecRestrictIf", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  avecRestrictZero(tableau, bitmasque, nb, &somme);
  fin = getCPUTime();
  afficheTemps("FonctionAvecRestrictZero", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  double s;
  fortranif_(tableau, bitmasque, & nb, &s);
  somme.valeurs[0] = s;
  fin = getCPUTime();
  afficheTemps("fortranIf", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  fortranzero_(tableau, bitmasque, & nb, &s);
  somme.valeurs[0] = s;
  fin = getCPUTime();
  afficheTemps("fortranZero", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  pthZero(tableau, bitmasque, nb, &somme);
  fin = getCPUTime();
  afficheTemps("pthZero", somme, nb, fin, debut);


  float *bloc= malloc(  sizeof(float) * nb );
  float *blocbit= malloc(  sizeof(float) * nb );
  for(int i=0;i<nb;i++) {
    bloc[i] = tableau[i].valeurs[0];
    blocbit[i] = bitmasque[i];
  }

  somme = zero;
  debut = getCPUTime();
  avecRestrictBlocZeroF(bloc, bitmasque, nb, &somme);
  fin = getCPUTime();
  afficheTemps("blocZeroF", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  avecRestrictBlocVectorZeroF(bloc, blocbit, nb, &somme);
  fin = getCPUTime();
  afficheTemps("blocVectorZeroF", somme, nb, fin, debut);

  somme = zero;
  debut = getCPUTime();
  fortranbloczero_(bloc, bitmasque, & nb, &s);
  somme.valeurs[0] = s;
  fin = getCPUTime();
  afficheTemps("fortranBlocZero", somme, nb, fin, debut);

}
