CC=gcc
CFLAGS=-c -Wall -lusb-1.0 ./libirecovery.a -I. -g
OS_TARGET=opensn0w
LIBS=-lusb-1.0 ./libirecovery.a
OBJS=main.o limera1n.o
all: opensn0w

opensn0w: $(OBJS)
	$(CC) main.o -o $(OS_TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o opensn0w
