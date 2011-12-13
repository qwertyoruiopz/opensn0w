CC=gcc
CFLAGS=-c -Wall -lusb-1.0 ./libirecovery.a -I.
OS_TARGET=opensn0w
LIBS=-lusb-1.0 -framework CoreFoundation ./libirecovery.a
all: opensn0w

opensn0w: main.o
	$(CC) main.o -o $(OS_TARGET) $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o opensn0w
