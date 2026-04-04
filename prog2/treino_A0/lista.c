#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

lista_t *lista_cria(){
    lista_t *l;
    no_t *no;

    if(!(l = malloc(sizeof(lista_t))))
        return NULL;

    if(!(no = malloc(sizeof(no_t)))){
        free(l);
        return NULL;
    }

    no->prox = no;
    no->ant = no;
    no->id = 0;
    no->prob = 0;

    l->ini = no;
    l->fim = no;
    l->tam = 0;
    
    return l;
}

void lista_destroi(lista_t **l){
    no_t *aux, *prox;

    aux = (*l)->ini->prox;
    while(aux != (*l)->ini){
        prox = aux->prox;
        free(aux);
        aux = prox;
    }

    free(aux);
    free(*l);
    *l = NULL;
}


void lista_insere(lista_t *l, int id, int prob){
    no_t *no, *aux;

    if(!(no = malloc(sizeof(no_t))))
        return;

    no->id = id;
    no->prob = prob;

    /*caso 1: lista vazia*/
    if(lista_vazia(l)){
        l->fim = no;
        l->ini->prox = no;
        l->ini->ant = no;
        no->prox = l->ini;
        no->ant = l->ini;
        
        l->tam++;

        return;
    }

    /*caso 2: inserir no comeco*/
    if(no->prob > l->ini->prox->prob){
        no->prox = l->ini->prox;
        no->ant = l->ini;
        l->ini->prox->ant = no; 
        l->ini->prox = no;

        l->tam++;

        return;
    }
    
    aux = l->ini->prox;

    /*procura posicao para inserir*/
    while(aux->prox != l->ini && no->prob < aux->prob)
        aux = aux->prox;

    /*caso 3: inserir no fim(while parou no sentinela)*/
    if(aux->prox == l->ini){
        no->ant = l->ini->ant;
        no->prox = l->ini;
        aux->prox = no;
        l->ini->ant->prox = no;
        l->ini->ant = no;

        l->tam++;

        return;
    }

    /*caso 4: inserir no entre dois nos*/
    aux->ant->prox = no;
    no->ant = aux->ant;
    no->prox = aux;
    aux->ant = no;

    l->tam++;
}

no_t *lista_remove(lista_t *l, int id){
    no_t *aux;

    aux = l->ini->prox;

    /*caso 1: remover o primeiro*/
    if(aux->id == id){
        aux->prox->ant = l->ini;
        l->ini->prox = aux->prox;
    }
    else{
        while(aux != l->ini && aux->id != id)
            aux = aux->prox;

        /*caso 2: elemento nao encontrado(aux vai parar no sentinela)*/
        if(aux == l->ini)
            return NULL;

        /*caso 3: remover o ultimo*/
        if(aux->prox == l->ini){
            l->ini->ant = aux->ant;
            aux->ant->prox = l->ini;
        }
        /*caso 4: remover do meio*/
        else{
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
        }
    }

    l->tam--;
    return aux;
}

int lista_tamanho(lista_t *l){
    return l->tam;
}

int lista_vazia(lista_t *l){
    if(lista_tamanho(l) == 0)
        return 1;
    
    return 0;
}