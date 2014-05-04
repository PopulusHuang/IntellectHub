obj=switch.o
CC=gcc
CGIDIR=../../www/cgi-bin/
LIBPATH=../../lib
INCPATH=../../include
LIB=cgic
app=$(CGIDIR)switch.cgi
CFLAGS=-L$(LIBPATH) -I$(INCPATH) -l$(LIB) -lgpio 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
