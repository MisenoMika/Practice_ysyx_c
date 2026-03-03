CFLAGS=-Wall -g
CC=gcc
all: game.exe

ex19.exe: ex19.o object.o
	$(CC) $(CFLAGS) -o ex19.exe ex19.o object.o

game.exe: game.o object.o newgame.o engine.o
	$(CC) $(CFLAGS) -o game.exe game.o object.o newgame.o engine.o

game.o: game.c newgame.h object.h engine.h
	$(CC) $(CFLAGS) -c game.c

ex19.o: ex19.c object.h 
	$(CC) $(CFLAGS) -c ex19.c 

object.o: object.c object.h
	$(CC) $(CFLAGS) -c object.c

newgame.o: newgame.c newgame.h object.h engine.h
	$(CC) $(CFLAGS) -c newgame.c

engine.o: engine.c engine.h object.h
	$(CC) $(CFLAGS) -c engine.c
	
clean: 
	rm -f ex19 game.exe *.o