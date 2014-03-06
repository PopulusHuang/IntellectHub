obj=show_dev.o
CC=gcc
CGIDIR=../../www/cgi-bin/
LIBPATH=../../lib
INCPATH=../../include
LIB=cgic
app=$(CGIDIR)show_dev.cgi
CFLAGS=-L$(LIBPATH) -I$(INCPATH) -l$(LIB) 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
