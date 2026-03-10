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

}


void lista_insere(lista_t *l, int id, int prob){
    no_t *no, *aux;

    if(!(no = malloc(sizeof(no_t))))
        return;

    no->id = id;
    no->prob = prob;

    /*caso 1: lista vazia*/
    if(lista_vazia(l)){
        lista->fim = no;
        lista->ini->prox = no;
        no->prox = lista->ini;
        no->ant = lista->ini;
        
        return;
    }

    /*caso 2: inserir no comeco*/
    if(no->prob > lista->ini->prox->prob){
        no->prox = lista->ini->prox;
        no->ant = lista->ini;
        lista->ini->prox->ant = no; 
        lista->ini->prox = no;

        return;
    }
    
    aux = lista->ini->prox;

    /*procura posicao para inserir*/
    while(aux->prox != lista->ini && no->prob < aux->prob)
        aux = aux->prox;

    /*caso 3: inserir no fim(while parou no sentinela)*/
    if(aux = lista->ini){
        no->ant = lista->ini->ant;
        no->prox = lista->ini;
        lista->ini->ant->ant->prox = no;

        return;
    }

    /*caso 4: inserir no entre dois nos*/
    
    
}

no_t *lista_remove(lista_t *l, int id){

}

int lista_tamanho(lista_t *l){
    return l->tam;
}

int lista_vazia(lista_t *l){
    if(lista_tamanho == 0)
        return 1;
    
    return 0;
}