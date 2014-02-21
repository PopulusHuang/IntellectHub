OBJ=cgic.o
CC=gcc
CFLAGS=-fpic -shared 

libcgic.so:$(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)
cleanlib:
	rm -f libcgic.so
cleanobj:
	rm -f *.o
cleanall:
	rm -f *.o libcgic.so
