CC = gcc
CFLAGS = -Wall -g

OBJS = main.o ponto.o heap.o guloso.o

# Alvos virtuais
.PHONY: programa clean tempo testes limpa

# Alvo padrão: compila o executável principal na raiz
programa: $(OBJS)
	$(CC) $(CFLAGS) -o programa $(OBJS) -lm

main.o: main.c ponto.h heap.h guloso.h
	$(CC) $(CFLAGS) -c main.c

ponto.o: ponto.c ponto.h
	$(CC) $(CFLAGS) -c ponto.c

heap.o: heap.c heap.h ponto.h
	$(CC) $(CFLAGS) -c heap.c

guloso.o: guloso.c guloso.h ponto.h heap.h
	$(CC) $(CFLAGS) -c guloso.c

# Remove apenas os objetos locais da compilação na raiz
clean:
	rm -f *.o programa

# Entra na pasta scripts, garante permissão e roda o teste de tempo
tempo: programa
	@chmod +x scripts/rodar_testes_tempo.sh
	@cd scripts && ./rodar_testes_tempo.sh

# Entra na pasta scripts, garante permissão e roda o valgrind com o nome correto
testes: programa
	@chmod +x scripts/rodar_testes_basicos.sh
	@cd scripts && ./rodar_testes_basicos.sh

# Faxina completa: limpa os .o da raiz e apaga o lixo pesado de dentro de scripts
limpa: clean
	@echo "Removendo pastas de testes temporários..."
	rm -rf TimeTests