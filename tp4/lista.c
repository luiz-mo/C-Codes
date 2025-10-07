#include "lista.h"
#include <stdlib.h>
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;
};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria (){
    struct lista *l;   

    if(!(l = malloc(sizeof(struct lista))))
        return NULL;

    l->ini = NULL;
    l->ptr = NULL;
    l->tamanho = 0;

    return l;
}

void lista_destroi (struct lista **lista){
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *n;

    if(!(n = malloc(sizeof(struct nodo))))
        return 0;

    nodo->chave = chave;
    nodo->prox = lista->ini;
    lista->ini = nodo;
    lista->tamanho++;

    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *n;

    if(!(n = malloc(sizeof(struct nodo))))
        return 0;

    nodo->chave = chave;
    nodo->prox = NULL;

    while(lista->ptr < lista->tamanho)
        lista_incrementa_iterador()

}

int lista_insere_ordenado (struct lista *lista, int chave){
}

int lista_remove_inicio (struct lista *lista, int *chave){
}

int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista){
    if(!(lista->tam))
        return 1;

    return 0;
}

int lista_tamanho (struct lista *lista){
    return lista->tam;
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    lista->ptr++;
    if(lista->ptr > lista->tamanho)
        return 0;

    *chave = lista->ptr->chave;
    return 1;
}
