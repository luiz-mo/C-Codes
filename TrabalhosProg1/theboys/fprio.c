#include <stdio.h>
#include <stdlib.h>

#include "fprio.h"

// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples

/*retorna 1 se o item ja existe na fila*/
int busca (struct fprio_t *f, void *item){
    struct fpnodo_t *aux;
    aux = f->prim;

    while(aux != NULL){
        if(aux->item == item)
            return 1;
        aux = aux->prox;
    }
    
    return 0;
}

struct fprio_t *fprio_cria (){
    struct fprio_t *f;

    if(!(f = malloc(sizeof(struct fprio_t))))
        return NULL;

    f->prim = NULL;
    f->fim = NULL;
    f->num = 0;
    return f;
}

struct fprio_t *fprio_destroi (struct fprio_t *f){
    struct fpnodo_t *aux, *prox;

    if(!f)
        return NULL;

    aux = f->prim;

    while(aux != NULL){
        prox = aux->prox;
        free(aux->item);
        free(aux);
        aux = prox;
    }

    free(f);
    f = NULL;
    
    return NULL;
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
    struct fpnodo_t *n, *aux;

    if(!f || !item)
        return -1;

    if(busca(f,item))
        return -1;
    
    if(!(n = malloc(sizeof(struct fpnodo_t))))
        return -1;

    n->item = item;
    n->tipo = tipo;
    n->prio = prio;
    n->prox = NULL;

    /*checa caso de fila vazia*/
    if(f->num == 0){
        f->prim = n;
        f->num++;
        return f->num;
    }

    f->num++; /*se chegou aqui, ja da pra aumentar o tamanho*/

    aux = f->prim;

    /*checa caso de fila com um elemento*/
    if(aux->prox == NULL){
        if(aux->prio <= prio)
            aux->prox = n;

        else{
            n->prox = aux;
            f->prim = n;
        }

        return f->num;
    }

    /*checa caso de inserir na primeira posicao*/
    if(aux->prio > prio){
        n->prox = f->prim;
        f->prim = n;

        return f->num;
    }

    while(aux->prox != NULL && aux->prox->prio <= prio ) 
        aux = aux->prox;
    
    n->prox = aux->prox;
    aux->prox = n;       

    return f->num;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
    struct fpnodo_t *aux;
    void *item;

    if(!f || !tipo || !prio || f->prim == NULL)
        return NULL;

    aux = f->prim;
    f->prim = aux->prox;

    item = aux->item; /*guarda o tipo do item para retornar*/
    *tipo = aux->tipo;
    *prio = aux->prio;
    free(aux);
    aux = NULL;
    f->num--;

    return item;
}

int fprio_tamanho (struct fprio_t *f){
    if(!f)
        return -1;

    return f->num;
}

void fprio_imprime (struct fprio_t *f){
    struct fpnodo_t *aux;

    if(!f || f->num == 0)
        return;

    aux = f->prim;

    while(aux->prox != NULL){
        printf("(%d %d) ", aux->tipo, aux->prio);
        aux = aux->prox;
    }

    printf("(%d %d)", aux->tipo, aux->prio);
}
