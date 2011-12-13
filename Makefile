CC=gcc
CFLAGS=-c -Wall -I.

all: opensn0w

opensn0w: main.o
	$(CC) main.o -o opensn0w

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o opensn0w
