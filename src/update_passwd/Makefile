ORG=update_passwd
obj=$(ORG).o
CC=gcc
DIR=$(shell pwd)/../../
CGIDIR=$(DIR)/www/cgi-bin/
LIBPATH=-L$(DIR)/lib
INCPATH=-I$(DIR)/include
LIBS=-lcgic -lsession -lsqlite3 -laccount
app=$(CGIDIR)$(ORG).cgi
CFLAGS=$(LIBPATH) $(INCPATH) $(LIBS) 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
clean:
	rm -f *.o $(app)
