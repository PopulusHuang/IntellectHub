DIR = $(shell pwd)/../../

obj=show_dev.o 
CC=gcc
CGIDIR=$(DIR)www/cgi-bin/
LIBPATH=$(DIR)lib
INCPATH=-I$(DIR)include
LIB=-lcgic -lgpio -ldevicesql -lsqlite3
app=$(CGIDIR)show_dev.cgi
CFLAGS=-L$(LIBPATH) $(INCPATH) $(LIB) 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
