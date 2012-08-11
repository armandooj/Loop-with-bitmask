#include <pthread.h>
#include "czero.h"
#include "pthzero.h"
#include "assert.h"

static void *pthzero_slave(struct pthzero_data *data) {
  avecRestrictZero(data.tab, data.bitmasque, data.nb, &data.somme);
  return 0;
}

void pthZero(const struct TripletD const * restrict tab,
	     const char const * restrict bitmasque,
	     int nb, struct TripletD * restrict somme) {
  pthread_t thrs[NBTHREADS];
  struct pthzero_data data[NBTHREADS];
  
  for(int i=0; i < NBTHREADS; i++) {
    data.tab = tab+(nb/NBTHREADS)*i;
    data.bitmasque = bitmasque +(nb/NBTHREADS) * i;
    data.nb = (nb/NBTHREADS);
    data.somme = 0;
  }
  
  for(int i=0; i < NBTHREADS; i++) {
    pthread_create(& thrs[i], 0, pthzero_slave, (void*) (data+i) );
  }

  for(int i=0; i < NBTHREADS; i++) {
    void *resul;
    pthread_join(thrs[i], &resul);
    assert(resul == 0);
  }

  
  for(int i=0; i < NBTHREADS; i++) {
    somme->valeurs[0] += data[i].somme.valeurs[0];
  }
}
