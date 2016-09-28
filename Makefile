LIB=./lib/
INC=./include/
BIN=./bin/
SRC=./src/
TST=./testes/

DIRS=$(LIB) $(INC) $(BIN) $(SRC) $(TST)

CTHREAD=libcthread.a

CC=gcc
CCFLAGS=-m32 -Wall -I$(INC)
LDFLAGS=-L$(LIB) -l:$(CTHREAD)

_OBJS=$(wildcard $(SRC)*.c)
OBJS=$(addprefix $(BIN), $(notdir $(_OBJS:.c=.o)))

_TSTS=$(wildcard $(TST)*.c)
TSTS=$(addprefix $(TST), $(notdir $(_TSTS:.c=)))


.PHONY: directories tests

all: directories $(OBJS)
	ar crs $(LIB)$(CTHREAD) $(BIN)support.o $(OBJS)

directories:
	mkdir -p -v $(DIRS)

tests: all $(TSTS)
	$(TSTS:%=% ;)

$(TST)%: $(TST)%.c
	$(CC) $(CCFLAGS) -o $@ $< $(LDFLAGS)

$(BIN)%.o: $(SRC)%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	find $(BIN) $(LIB) $(TST) -type f ! -name 'support.o' ! -name "*.c" -delete
