orignal=device_list
obj=$(orignal).o ../share/device_sql.o ../share/read_rfid.o
CC=gcc
CGIDIR=../../www/cgi-bin/
LIBPATH=../../lib
INCPATH=../../include
LIB=cgic
app=$(CGIDIR)$(orignal).cgi
CFLAGS=-L$(LIBPATH) -I$(INCPATH) -l$(LIB) -lsqlite3 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
