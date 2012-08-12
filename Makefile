
CFLAGS=-std=gnu11 -O3 -funroll-all-loops -fbranch-probabilities
LDLIBS=-lrt 
FC=gfortran
FFLAGS=-O3 -funroll-all-loops -fbranch-probabilities

loopandbitmask: loopandbitmask.o zero.o czero.o pthzero.o bloczero.o 


clean:
	rm -f *.o loopandbitmask


profile: CFLAGS+= -fprofile-arcs
profile: LDLIBS+= -lgcov
profile: clean loopandbitmask

probabilities: CLAFGS+= -fbranch-probabilities
probabilities: clean loopandbitmask 

clean-profile:
	rm -f *.gcda
