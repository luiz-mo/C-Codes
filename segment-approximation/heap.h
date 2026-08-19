#ifndef HEAP_H
#define HEAP_H

#include "ponto.h"

typedef struct{
    int indice;
    float erro; /*prioridade*/
} No;

typedef struct{
    No *v;
    int *posicao; /*tabela de simbolos*/
    int tam;
    int capacidade;
} Heap;

Heap *cria_heap(int n);

int insere_heap(Heap *heap, int indice_ponto);

int extrai_min_heap(Heap *heap);

int atualiza_heap(Heap *heap, int indice_ponto);

Heap *destroi_heap(Heap *heap);

#endif