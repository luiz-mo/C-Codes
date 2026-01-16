CFLAGS = -Wall -Wextra -g -std=c99 # flags de compilacao
CC = gcc

# gera o executável
all: progteste.o busca.o sorts.o
    $(CC) -o progteste progteste.o busca.o sorts.o

# compila busca.c
busca.o: busca.c busca.h
    $(CC) -c $(CFLAGS) busca.c

# compila sorts.c
sorts.o: sorts.c sorts.h
	$(CC) -c $(CFLAGS) sorts.c

# compila progteste.c
progteste.o: progteste.c busca.h sorts.h
    $(CC) -c $(CFLAGS) progteste.c

clean:
    rm -f *.o *~ tp1
