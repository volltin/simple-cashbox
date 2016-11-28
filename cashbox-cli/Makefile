TARGET=cashbox
CC=gcc
CFLAGS=-g -Wall
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

all: ${TARGET}
clean: 
	find . -name \*.o -delete
	rm -f cashbox

$(TARGET): ${OBJECTS}
	${CC} ${CFLAGS} -o ${TARGET} ${OBJECTS}
