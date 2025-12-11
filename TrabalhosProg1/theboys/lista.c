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

    if(!(l = malloc(sizeof(struct lista)))) /*tenta alocar lista*/
        return 0;

    l->ini = NULL;
    l->ptr = NULL;
    l->tamanho = 0;

    return l;
}

void lista_destroi (struct lista **lista){
    struct nodo *aux,*prox;

    if(!*lista)
        return;

    aux = (*lista)->ini;
    while(aux != NULL){
        prox = aux->prox;
        free(aux);
        aux = prox;
    }
    free(*lista);
    *lista = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *n;

    if(!lista || !(n = malloc(sizeof(struct nodo))))
        return 0;

    n->chave = chave;
    n->prox = lista->ini;
    lista->ini = n;
    lista->tamanho++;

    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *n, *aux;

    if(!lista || !(n = malloc(sizeof(struct nodo))))
        return 0;

    aux = lista->ini;

    n->chave = chave;
    n->prox = NULL;

    if(lista->tamanho == 0){
        lista->ini = n;
        lista->tamanho++;

        return 1;
    }

    while(aux->prox != NULL)
        aux = aux->prox;

    aux->prox = n;
    lista->tamanho++;
    
    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
    struct nodo *n, *aux;

    if(!lista || !(n = malloc(sizeof(struct nodo))))
        return 0;

    n->chave = chave;

    if(lista_vazia(lista)){
        lista->ini = n;
        n->prox = NULL;
        lista->tamanho++;

        return 1;
    }

    if(chave <= lista->ini->chave){
        n->prox = lista->ini;
        lista->ini = n;
        lista->tamanho++;

        return 1;
    }

    aux = lista->ini;
        
    while(aux->prox != NULL && chave > aux->prox->chave)
        aux = aux->prox;
    
    n->prox = aux->prox;
    aux->prox = n;
    lista->tamanho++;
    
    return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave){
    if(!lista || lista_vazia(lista))
        return 0;
    
    struct nodo *aux;

    aux = lista->ini;
    *chave = aux->chave;
    lista->ini = aux->prox;

    free(aux);
    aux = NULL;
    lista->tamanho--;

    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    if(!lista || lista_vazia(lista))
        return 0;

    struct nodo *aux;

    aux = lista->ini;

    if(lista->tamanho == 1){
        *chave = aux->chave;
        lista->ini = NULL;
        free(aux);
        lista->tamanho--;

        return 1;
    }

    if(lista->tamanho > 1) /*verifica se o penultimo nodo existe*/
        while(aux->prox->prox != NULL) /*para no penultimo nodo*/
            aux = aux->prox;
    
    *chave = aux->prox->chave;
    
    free(aux->prox);
    aux->prox = NULL;
    lista->tamanho--;
    
    return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave){
    if(!lista || lista_vazia(lista))
        return 0;

    struct nodo *aux,*p;

    if(lista->ini->chave == chave){
        aux = lista->ini;
        lista->ini = lista->ini->prox;
        free(aux);
        lista->tamanho--;

        return 1;
    }

    aux = lista->ini;
    
    while(aux->prox != NULL && chave != aux->prox->chave)
        aux = aux->prox;

    if(aux->prox == NULL) /*elemento nao encontrado*/
        return 0;
    
    p = aux->prox;
    aux->prox = aux->prox->prox;
    free(p);
    p = NULL;
    lista->tamanho--;

    return 1;
}

int lista_vazia (struct lista *lista){
    if(!lista)
    return 0;
    
    if(!(lista->tamanho))
        return 1;

    return 0;
}

int lista_tamanho (struct lista *lista){
    return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
    struct nodo *aux;
    
    aux = lista->ini;

    while(aux != NULL){
        if(aux->chave == chave)
            return 1;
        aux = aux->prox;
    }

    return 0; /*se chegou aqui, significa que o elemento nao foi encontrado*/
}

void lista_inicia_iterador (struct lista *lista){
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    if(!lista || lista->ptr == NULL)
        return 0;

    *chave = lista->ptr->chave;
    lista->ptr = lista->ptr->prox;
    return 1;
}
