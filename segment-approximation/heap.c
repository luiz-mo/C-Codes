#include <stdlib.h>
#include <float.h>

#include "heap.h"

void troca(Heap *heap, int i, int j){
    No aux = heap->v[i];
    heap->v[i] = heap->v[j];
    heap->v[j] = aux;

    heap->posicao[heap->v[i].indice] = i;
    heap->posicao[heap->v[j].indice] = j;
}

void sacode_heap(Heap *heap, int i){
    while(i*2 <= heap->tam){
        int filho = i*2;
        if(filho < heap->tam && heap->v[filho].erro > heap->v[filho+1].erro)
            filho++;

        if(heap->v[i].erro <= heap->v[filho].erro) /*eh heap*/
            break;

        troca(heap, i, filho);
        i = filho;
    }
}

Heap *cria_heap(int n){
    Heap *heap;

    if(!(heap = malloc(sizeof(Heap))))
        return NULL;

    if(!(heap->v = malloc(sizeof(No) * (n + 1)))){
        free(heap);
        heap = NULL;

        return NULL;
    }

    if(!(heap->posicao = malloc(sizeof(int) * (n+1)))){
        free(heap->v);
        heap->v = NULL;

        free(heap);
        heap = NULL;

        return NULL;
    }

    heap->v[0].erro = -FLT_MAX;

    int i;
    for(i=0;i <= n;i++)
        heap->posicao[i] = -1;

    heap->tam = 0;
    heap->capacidade = n;

    return heap;
}

int insere_heap(Heap *heap, int indice_ponto){
    No novo;

    if(!heap)
        return 1;

    if(heap->tam == heap->capacidade)
        return 1;

    novo.indice = indice_ponto;
    novo.erro = pontos[indice_ponto].erro;
    
    heap->tam++;
    heap->v[heap->tam] = novo; /*insere no final do heap*/

    int i = heap->tam;
    heap->posicao[indice_ponto] = i;

    while(heap->v[i].erro < heap->v[i/2].erro){
        troca(heap, i, i/2);
        i /= 2;
    }

    return 0;
}

int extrai_min_heap(Heap *heap){
    if(!heap)
        return -1;

    if (heap->tam == 0)
        return -1;

    int removido = heap->v[1].indice;
    heap->posicao[removido] = -1;

    if(heap->tam > 1){
        heap->v[1] = heap->v[heap->tam];
        heap->posicao[heap->v[1].indice] = 1;
    }

    heap->tam--;

    sacode_heap(heap, 1);

    return removido;
}

int atualiza_heap(Heap *heap, int indice_ponto){
    if(!heap)
        return 1;

    int i = heap->posicao[indice_ponto];
    if(i == -1)
        return 1;

    float erro_ant = heap->v[i].erro;

    heap->v[i].erro = pontos[indice_ponto].erro;

    if(heap->v[i].erro > erro_ant)
        sacode_heap(heap, i);
    else if(heap->v[i].erro < erro_ant){
        while(heap->v[i].erro < heap->v[i/2].erro){
            troca(heap, i, i/2);
            i /= 2;
        }
    }

    return 0;
}

Heap *destroi_heap(Heap *heap){
    if(!heap)
        return NULL;

    free(heap->v);
    heap->v = NULL;

    free(heap->posicao);
    heap->posicao = NULL;

    free(heap);
    heap = NULL;

    return heap;
}