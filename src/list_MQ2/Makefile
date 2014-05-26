orignal=list_MQ2
obj=$(orignal).o 
CC=gcc
DIR=$(shell pwd)/../../
CGIDIR=$(DIR)/www/cgi-bin/

LIBPATH=-L$(DIR)/lib
INCPATH=-I$(DIR)/include

LIBS=-lcgic -lsqlite3 -ldevicesql
app=$(CGIDIR)$(orignal).cgi

CFLAGS=$(LIBPATH) $(INCPATH) $(LIBS) 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
