obj=login.o account.o
CC=gcc
CGIDIR=../../www/cgi-bin/
LIBPATH=../../lib
INCPATH=../../include
app=$(CGIDIR)login.cgi
CFLAGS=-L$(LIBPATH) -I$(INCPATH) -lcgic -lsession -lsqlite3
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
clean:
	rm -f *.o $(app)
