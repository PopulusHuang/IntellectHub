ORG=cgic
OBJ=$(ORG).o
CC=gcc
INCPATH=-I../../include
CFLAGS=-fpic -shared $(INCPATH)
TARGET=../lib$(ORG).so
$(TARGET):$(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)
cleanlib:
	rm -f $(TARGET)
cleanobj:
	rm -f *.o
cleanall:
	rm -f *.o $(TARGET)
