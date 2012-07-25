//#include <bool.h>
#include <time.h>
#include "loopandbitmask.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

char *bitmasque;
struct TripletD *tableau;




int main(int argc, char **argv)
{
  assert(argc == 2);
  int nb = atoi(argv[1] );
  struct timespec debut, fin;
  struct TripletD somme = {};

  bitmasque = malloc( sizeof(char) * nb);
  tableau = malloc( sizeof(struct TripletD) * nb);
  
  for(int i=0; i < nb; i++)
    {
      bitmasque[i] = (drand48() < 0.5)?1:0;
      for(int j=0; j < 3; j++) {
	tableau[i].valeurs[j] = drand48();
      }
    }

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & debut);
  for(int i=0; i < nb; i++) {
    somme.valeurs[0] += tableau[i].valeurs[0]; 
    //somme.valeurs[1] += tableau[i].valeurs[1]; 
    //somme.valeurs[2] += tableau[i].valeurs[2];
  } 
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & fin); 
  double temps = 1.0*(fin.tv_sec - debut.tv_sec)+1E-9*(fin.tv_nsec - debut.tv_nsec);
  printf("somme0: %le; temps %le, acc/s %le\n",
	 somme.valeurs[0]+somme.valeurs[1]+somme.valeurs[2],
	 temps,
	 nb / temps);

  struct TripletD zero = {};
  somme = zero;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & debut);
  for(int i=0; i < nb; i++) {
    if (bitmasque[i]) {
      somme.valeurs[0] += tableau[i].valeurs[0]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
    }
  } 
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & fin); 
  temps = 1.0*(fin.tv_sec - debut.tv_sec)+1E-9*(fin.tv_nsec - debut.tv_nsec);
  printf("somme2: %le; temps %le, acc/s %le\n",
	 somme.valeurs[0]+somme.valeurs[1]+somme.valeurs[2],
	 temps,
	 nb / temps);
  

  somme = zero;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & debut);
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
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & fin); 
  temps = 1.0*(fin.tv_sec - debut.tv_sec)+1E-9*(fin.tv_nsec - debut.tv_nsec);
  printf("somme3: %le; temps %le, acc/s %le\n",
	 somme.valeurs[0]+somme.valeurs[1]+somme.valeurs[2],
	 temps,
	 nb / temps);

  somme = zero;


  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & debut);
  double *dense = malloc( sizeof(double) * nb );
  int pos;
  for(int i=0;i<nb;i++) {
    if (bitmasque[i]) {
      dense[pos] = tableau[i].valeurs[0];
      pos ++;
    }
  }

  for(int i=0; i < pos; i++) {
      somme.valeurs[0] += dense[i]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
  } 
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & fin); 
  temps = 1.0*(fin.tv_sec - debut.tv_sec)+1E-9*(fin.tv_nsec - debut.tv_nsec);
  printf("somme4: %le; temps %le, acc/s %le\n",
	 somme.valeurs[0]+somme.valeurs[1]+somme.valeurs[2],
	 temps,
	 nb / temps);

  somme = zero;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & debut);
  for(int i=0; i < nb; i++) {
    somme.valeurs[0] += bitmasque[i] * tableau[i].valeurs[0]; 
      //somme.valeurs[1] += tableau[i].valeurs[1]; 
      //somme.valeurs[2] += tableau[i].valeurs[2];
  } 
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, & fin); 
  temps = 1.0*(fin.tv_sec - debut.tv_sec)+1E-9*(fin.tv_nsec - debut.tv_nsec);
  printf("somme5: %le; temps %le, acc/s %le\n",
	 somme.valeurs[0]+somme.valeurs[1]+somme.valeurs[2],
	 temps,
	 nb / temps);
  


}
