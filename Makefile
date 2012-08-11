
CFLAGS=-std=gnu11 -O3 -funroll-all-loops -ftree-vectorize
LDLIBS=-lrt
FC=gfortran
FFLAGS=-O3 -g -funroll-all-loops -ftree-vectorize

loopandbitmask: loopandbitmask.o zero.o


clean:
	rm -f *.o loopandbitmask
