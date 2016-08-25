cc = gcc
CFLAGS = -Wall -pedantic -ansi

all: game
game: utils.o
	${cc} ${CFLAGS} -g -o game game.c utils.o

utils.o: utils.h
	${cc} ${CFLAGS} -g -c -o utils.o utils.c

player.o: player.h
	${cc} ${CFLAGS} -g -c -o utils.o utils.c

.PHONY clean:
	-rm game *.o
