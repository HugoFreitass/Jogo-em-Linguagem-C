CC = gcc

all: tetris

tetris: tetris.o libtetris.o
	$(CC) tetris.o -o tetris libtetris.o -lncurses

libtetris.o: libtetris.c libtetris.h
	$(CC) libtetris.h
	$(CC) -c libtetris.c -o libtetris.o

tetris.o: tetris.c 
	$(CC) -c tetris.c -o tetris.o

clean:
	rm -f *.o *.gch tetris
