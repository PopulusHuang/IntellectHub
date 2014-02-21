obj=login.o account.o
CC=gcc
CGIDIR=../../www/cgi-bin/
LIBPATH=../../lib
INCPATH=../../include
LIB=cgic
app=$(CGIDIR)login.cgi
CFLAGS=-L$(LIBPATH) -I$(INCPATH) -l$(LIB) -lsqlite3
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
