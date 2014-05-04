OBJ=gpio_test.o
CC=gcc
INCPATH=../../include
LIBPATH=../../lib
LIB=gpio
CFLAGS=-L$(LIBPATH) -I$(INCPATH) -l$(LIB)
TARGET=gpio_test
$(TARGET):$(OBJ)
	$(CC) -o $(TARGET)  $(OBJ) $(CFLAGS)
clean:
	rm -rf $(TARGET)
	rm -rf *.o
