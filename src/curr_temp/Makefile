orignal=curr_temp
obj=$(orignal).o 
CC=gcc
DIR=$(shell pwd)/../../
CGIDIR=$(DIR)/www/cgi-bin/

LIBPATH=-L$(DIR)/lib
INCPATH=-I$(DIR)/include

LIBS=-lcgic 
app=$(CGIDIR)$(orignal).cgi

CFLAGS=$(LIBPATH) $(INCPATH) $(LIBS) 
$(app):$(obj)
	$(CC) -o $@  $(obj) $(CFLAGS)
cleanobj:
	rm -rf *.o
cleancgi:
	rm -rf $(app)
cleanall:
	rm -f *.o $(app)
