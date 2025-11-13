#include "inicializacoes.h"
#include "conjunto.h"
#include "entidades.h"

/*
para as chamadas de rand:
somar com o valor minimo garante que o intervalo comece no valor minimo 
%(maximo-minimo-1) delimita o tamanho do intervalo 
*/

int inicializa_heroi(struct mundo *w, int id){
    struct heroi *h;
    int i, hab;

    if(!(h = malloc(sizeof(struct heroi))))
        return 0;
    
    h->id = id;
    h->experiencia = 0;
    h->paciencia = P_MIN + rand()%(P_MAX-P_MIN+1);
    h->velocidade = V_MIN + rand()%(V_MAX-V_MIN+1);
    h->habilidades->cap = HAB_MIN + rand()%(HAB_MAX-HAB_MIN+1);
    for(i=0;i < h->habilidades->cap;i++){
        hab = 1  + rand()%(N_HABILIDADES+1);
        cjto_insere(h->habilidades,hab);
    }

    w->herois[id] = h;
}

int inicializa_base(struct mundo *w, int id){
    struct base *b;

    b->id = id; 
}

int inicializa_missao(struct mundo *w, int id){

}

int inicializa_mundo(struct mundo *w){
    int i;

    if(!(w = malloc(sizeof(struct mundo))))
        return 0;

    for(i=0;i < w->n_herois;i++)
        inicializa_heroi(w,i);

    for(i=0;i < w->n_bases;i++)
        inicializa_base(w,i);

    for(i=0;i < w->n_missoes;i++)
        inicializa_missao(w,i);
}