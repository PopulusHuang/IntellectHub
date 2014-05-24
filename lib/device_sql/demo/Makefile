OBJS=devicesql_test.o devicesql.o
DIR=$(shell pwd)/../../
INC=-I$(DIR)/../include
CFLAGS= $(INC) -g -lsqlite3
test:$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)
clean:
	rm -rf *.o
	rm -rf test
