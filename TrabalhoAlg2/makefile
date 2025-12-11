CFLAGS = -Wall -Wextra -g -std=c99
CC = gcc

all: main log

main: main.o heap.o sorts.o
	$(CC) -o main main.o heap.o sorts.o

log: log.o heap.o sorts.o
	$(CC) -o log log.o heap.o sorts.o

heap.o: heap.c heap.h
	$(CC) -c $(CFLAGS) heap.c

sorts.o: sorts.c sorts.h
	$(CC) -c $(CFLAGS) sorts.c

main.o: main.c heap.h sorts.h
	$(CC) -c $(CFLAGS) main.c

log.o: log.c heap.h
	$(CC) -c $(CFLAGS) log.c

clean:
	rm -f *.o *~ main log
