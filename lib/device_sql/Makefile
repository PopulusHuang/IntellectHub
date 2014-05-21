APP=devicesql
OBJ=$(APP).o
DIR=../
target=$(DIR)lib$(APP).so
INCLUDE=-I../../include
CC=gcc
CFLAGS=-fpic -shared $(INCLUDE)
$(target):$(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)
clean:
	rm -r $(target)
	rm -r *.o
