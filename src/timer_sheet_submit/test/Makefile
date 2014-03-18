obj=update.o
CC=gcc
CFLAGS=-lsqlite3
update_sheet:$(obj)
	$(CC) -o $@ $(obj) $(CFLAGS)
clean:
	rm -rf *.o
	rm -rf update

