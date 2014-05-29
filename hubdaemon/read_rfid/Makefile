ORG = read_rfid
OBJ = $(ORG).o
CC = gcc
DIR=$(shell pwd)/../../
INCS=-I$(DIR)/include/
LIBPATH=$(DIR)/lib/
LIBS=-ldevicesql -lsqlite3 
CFLAGS= $(INCS) -L$(LIBPATH) $(LIBS) -g
TARGET = $(ORG)
$(TARGET):$(OBJ)
	$(CC)  -o $@  $(OBJ) $(CFLAGS)
clean:
	rm -rf *.o
	rm -rf $(TARGET)
