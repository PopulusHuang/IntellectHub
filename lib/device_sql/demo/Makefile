OBJS=devicesql_test.o
DIR=$(shell pwd)/../../

INCS=-I$(DIR)/../include
LIBPATH=-L$(DIR)
LIBS=-lsqlite3 -ldevicesql
CFLAGS= $(INCS) $(LIBPATH) $(LIBS) -g
CC=gcc
test:$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)
clean:
	rm -rf *.o
	rm -rf test
