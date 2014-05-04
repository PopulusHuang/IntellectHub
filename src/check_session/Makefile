ORG=check_session
OBJ=$(ORG).o
CC=gcc
CGIDIR=../../www/cgi-bin/
LIBPATH=../../lib
INCPATH=../../include
TARGET=$(CGIDIR)$(ORG).cgi
CFLAGS=-L$(LIBPATH) -I$(INCPATH) -lcgic -lsession -lsqlite3
$(TARGET):$(OBJ)
	$(CC) -o $@  $(OBJ) $(CFLAGS)
clean:
	rm -f *.o $(TARGET)
