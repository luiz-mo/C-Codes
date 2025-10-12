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

    n->chave = chave;
    n->prox = lista->ini;
    lista->ini = n;
    lista->tamanho++;

    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *n;

    if(!(n = malloc(sizeof(struct nodo))))
        return 0;

    n->chave = chave;
    n->prox = NULL;

    lista_inicia_iterador(lista);
    while(lista->ptr->prox != NULL)
        lista_incrementa_iterador(lista,&chave);

    lista->ptr->prox = n;
    lista->tamanho++;
    
    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
    struct nodo *n;

    if(!(n = malloc(sizeof(struct nodo))))
        return 0;
    n->chave = chave;
    n->prox = NULL;

    lista_inicia_iterador(lista);

    if(chave < lista->ptr->chave){
        n->prox = lista->ini;
        lista->ini = n;
    }
        
    while(lista->ptr->prox != NULL && chave > lista->ptr->prox->chave)
        lista_incrementa_iterador(lista,chave);
    n->prox = lista->ptr->prox;
    lista->ptr->prox = n;
}

int lista_remove_inicio (struct lista *lista, int *chave){
    if(lista->tamanho == 0)
        return 0;
    
    struct nodo *aux;

    aux = lista->ini;
    lista->ini = lista->ini->prox;

    free(aux);
    aux = NULL;
    lista->tamanho--;

    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    if(lista->tamanho == 0)
        return 0;

    struct nodo *aux;

    lista_inicia_iterador(lista);
    while(lista->ptr->prox != NULL)
        lista_incrementa_iterador(lista,&chave);
    
    aux = lista->ptr;
    *chave = lista->ptr->chave;
    lista->ptr = NULL;

    free(aux);
    aux = NULL;
    lista->tamanho--;
    
    return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave){

}

int lista_vazia (struct lista *lista){
    if(!(lista->tamanho))
        return 1;

    return 0;
}

int lista_tamanho (struct lista *lista){
    return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
    lista_inicia_iterador(lista);

    while(lista->ptr->prox != NULL){
        if(lista->ptr->chave == chave)
            return 1;
        lista_incrementa_iterador(lista,&lista->ptr->chave);
    }

    return 0; /*se chegou aqui, significa que o elemento nao foi encontrado*/
}

void lista_inicia_iterador (struct lista *lista){
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    lista->ptr = lista->ptr->prox;
    if(lista->ptr->prox = NULL)
        return 0;

    *chave = lista->ptr->chave;
    return 1;
}
