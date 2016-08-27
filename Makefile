CC=gcc
LIB=./lib/
INC=./include/
BIN=./bin/
SRC=./src/
OBJ=

all: $(OBJ)
	ar crs $(LIB)libcthread.a $(OBJ) $(BIN)support.o

%.o: $(SRC)%.c
	$(CC) -m32 -o $(BIN)$@ -c $< -Wall -I$(INC)

clean:
	find $(BIN) $(LIB) -type f ! -name 'support.o' -delete
