TARGET=cashbox
CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0` -g -Wall
LDFLAGS=`pkg-config --libs gtk+-3.0` -export-dynamic
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

all: ${TARGET}
clean: 
	find . -name \*.o -delete
	rm -f cashbox

$(TARGET): ${OBJECTS}
	${CC} ${CFLAGS} -o ${TARGET} ${OBJECTS} ${LDFLAGS}
