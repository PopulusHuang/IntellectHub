obj=login.o
CC=gcc
DIR=$(shell pwd)/../../
CGIDIR=$(DIR)/www/cgi-bin/
LIBPATH=-L$(DIR)/lib
INCPATH=-I$(DIR)/include
LIBS=-lcgic -lsession -lsqlite3 -laccount
app=$(CGIDIR)login.cgi
CFLAGS=$(LIBPATH) $(INCPATH) $(LIBS) 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
clean:
	rm -f *.o $(app)
