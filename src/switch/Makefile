OBJ=switch.o
CC=gcc
DIR=$(shell pwd)/../../
CGIDIR=$(DIR)/www/cgi-bin/
LIBPATH=-L$(DIR)lib
INCPATH=-I$(DIR)include
LIBS=-lcgic -ldevicesql -lsqlite3 
app=$(CGIDIR)switch.cgi
CFLAGS=$(LIBPATH) $(INCPATH) $(LIBS) -lgpio  
$(app):$(OBJ)
	$(CC) -o $@  $(OBJ) $(CFLAGS)
cleanOBJ:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
