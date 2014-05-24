OBJ=gpio_test.o
DIR=$(shell pwd)/../../
LIBPATH=-L$(DIR)/
LIB=-lgpio
CC=gcc
CFLAGS=$(LIBPATH) $(LIB)
gpio_test:$(OBJ)
	$(CC) -o $@  $(OBJ) $(CFLAGS)
clean:
	rm -rf *.o 
	rm -rf gpio_test

