CC=gcc
CFLAGS=-c -Wall -I. -I/opt/local/include
OS_TARGET=opensn0w
LIBS=-lusb-1.0 -framework CoreFoundation ./libirecovery.a -L/opt/local/include
all: opensn0w

opensn0w: main.o
	$(CC) main.o -o $(OS_TARGET) $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o opensn0w
