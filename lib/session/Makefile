ORG=session
OBJ=$(ORG).o
INCPATH=-I../../include
DIR=../
TARGET=$(DIR)lib$(ORG).so
CFLAGS=$(INCPATH) -fpic -shared 
CC=gcc
$(TARGET):$(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)
clean:
	rm -rf $(TARGET)
	rm -rf *.o
