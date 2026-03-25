CFLAGS = -g -Wall -I. -I../ex20
CC = gcc
all: ex22.exe
ex22.exe: ex22.o ex22_main.o
	$(CC) $(CFLAGS) -o ex22.exe ex22.o ex22_main.o
ex22.o: ex22.c ex22.h ../ex20/dbg.h
	$(CC) $(CFLAGS) -c ex22.c 
ex22_main.o: ex22_main.c ex22.h ../ex20/dbg.h
	$(CC) $(CFLAGS) -c ex22_main.c
clean:
	rm -f ex22.exe *.o