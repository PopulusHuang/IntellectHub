ORG=account_test
obj=$(ORG).o
CC=gcc
DIR=$(shell pwd)/../../
LIBPATH=-L$(DIR)/
INCPATH=-I$(DIR)/../include
LIBS=-laccount -lsqlite3
CFLAGS=$(LIBPATH) $(INCPATH) $(LIBS) 
$(ORG):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
clean:
	rm -f *.o $(app)
