orignal=timer_sheet_submit
OBJ=$(orignal).o sheet_sql.o
CC=gcc
DIR=$(shell pwd)/../../
CGIDIR=$(DIR)/www/cgi-bin/
LIBPATH=$(DIR)/lib
INCPATH=-I$(DIR)/include
LIBS=-lcgic -lsqlite3 -ldevicesql
CGI=$(CGIDIR)$(orignal).cgi
CFLAGS=-L$(LIBPATH) $(INCPATH) $(LIBS) -g
$(CGI):$(OBJ)
	$(CC) -o $@  $(OBJ) $(CFLAGS)
cleanOBJ:
	rm -rf *.o
cleancgi:
	rm -rf $(CGI)
cleanall:
	rm -f *.o $(CGI)
