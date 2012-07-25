
CFLAGS=-std=gnu11 -O3 -funroll-all-loops -ftree-vectorize
LDLIBS=-lrt

loopandbitmask: loopandbitmask.o


clean:
	rm -f *.o loopandbitmask
