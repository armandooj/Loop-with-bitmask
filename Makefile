
CFLAGS=-g -std=gnu11 -O3 -funroll-all-loops -fbranch-probabilities
#-fprofile-arcs
LDLIBS=-lrt 
# -lgcov
FC=gfortran
FFLAGS=-O3 -g -funroll-all-loops -fbranch-probabilities
#-fbranch-probabilities

loopandbitmask: loopandbitmask.o zero.o czero.o pthzero.o bloczero.o


clean:
	rm -f *.o loopandbitmask
