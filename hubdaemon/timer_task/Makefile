ORG=timer_task
OBJ=$(ORG).o  devicesql.o gpio.o
CC=gcc
DIR=$(shell pwd)/../../
INCS=-I$(DIR)/include/
LIBPATH=-L$(DIR)/lib/
LIBS=-lsqlite3 #-lgpio #-ldevicesql  

CFLAGS=$(INCS) $(LIBPATH) $(LIBS) -g
TARGET = /home/ubuntu/daemond/$(ORG)
#TARGET=./$(ORG)
$(TARGET):$(OBJ)
	$(CC)  -o $@  $(OBJ) $(CFLAGS)
clean:
	rm -rf *.o
	rm -rf $(TARGET)
