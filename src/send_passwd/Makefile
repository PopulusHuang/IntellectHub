obj=send_passwd.o
CC=gcc
DIR=$(shell pwd)/../../
CGIDIR=$(DIR)/www/cgi-bin/
LIBPATH=-L$(DIR)/lib
INCPATH=-I$(DIR)/include
LIBS=-lcgic -lsession -lsqlite3 -laccount
app=$(CGIDIR)send_passwd.cgi
#app=./send_passwd.cgi
CFLAGS=$(LIBPATH) $(INCPATH) $(LIBS) 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
clean:
	rm -f *.o $(app)
