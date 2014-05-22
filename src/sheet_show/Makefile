obj=sheet_show.o ../share/sheet_sql.o
CC=gcc
DIR=$(shell pwd)/../../
CGIDIR=$(DIR)/www/cgi-bin/
INCPATH=-I$(DIR)/include

LIBPATH=-L$(DIR)/lib
LIBS=-lcgic -lsqlite3  -ldevicesql
app=$(CGIDIR)sheet_show.cgi
CFLAGS=$(LIBPATH) $(INCPATH) $(LIBS) 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
