#include <stdlib.h>

#include "inicializacoes.h"
#include "conjunto.h"
#include "entidades.h"


/*retorna um numero aleatorio no intervalo de min ate max*/
int aleat(int min, int max){
    return min+rand()%(max-min+1);
}

int inicializa_heroi(struct mundo *w, int id){
    struct heroi *h;

    if(!(h = malloc(sizeof(struct heroi))))
        return 0;
    
    h->id = id;

    h->experiencia = 0;
    h->paciencia = aleat(P_MIN,P_MAX);
    h->velocidade = aleat(V_MIN,V_MAX);
    h->base = -1; 
    h->vivo = 1; 
    
    h->habilidades = cjto_aleat(aleat(1,3),N_HABILIDADES);

    /*checa se o conjunto de habilidades foi alocado*/
    if(!h->habilidades){
        free(h);
        return 0;
    }

    w->herois[id] = h;

    return 1;
}

int inicializa_base(struct mundo *w, int id){
    struct base *b;

    if(!(b = malloc(sizeof(struct base))))
        return 0;

    b->id = id; 

    b->missoes_feitas = 0;

    b->local.x = aleat(COORD_MIN,COORD_MAX);
    b->local.y = aleat(COORD_MIN,COORD_MAX);

    b->lotacao = aleat(LOT_MIN,LOT_MAX);
    b->presentes = cjto_cria(w->n_herois);

    /*checa se o conjunto de presentes foi alocado*/
    if(!b->presentes){
        free(b);
        return 0;
    }

    b->fila_espera = lista_cria();

    /*checa se a fila de espera foi alocada*/
    if(!b->fila_espera){
        free(b->presentes);
        free(b);
        return 0;
    }

    b->max_espera = 0;

    w->bases[id] = b;

    return 1;
}

int inicializa_missao(struct mundo *w, int id){
    struct missao *m;

    if(!(m = malloc(sizeof(struct missao))))
        return 0;

    m->id = id;
    m->cumprida = 0;
    m->tentativas = 0;

    m->local.x = aleat(COORD_MIN,COORD_MAX);
    m->local.y = aleat(COORD_MIN,COORD_MAX);
    
    m->habilidades = cjto_aleat(aleat(HAB_N_MIN,HAB_N_MAX),w->n_habilidades);

    if(!m->habilidades){
        free(m);
        return 0;
    }

    w->missoes[id] = m;

    return 1;
}

struct mundo *inicializa_mundo(){
    struct mundo *w;
    int i;

    if(!(w = malloc(sizeof(struct mundo))))
        return NULL;

    w->n_bases = N_BASES;
    w->n_herois = N_HEROIS;
    w->n_missoes = N_MISSOES;
    w->n_habilidades = N_HABILIDADES;
    w->n_compostosV = N_COMPOSTOS_V;
    w->tam.x = N_TAMANHO_MUNDO;
    w->tam.y = N_TAMANHO_MUNDO;
    w->eventos_tratados = 0;
    w->herois_mortos = 0;
    w->missoes_cumpridas = 0;

    /*tenta alocar vetor de herois*/
    if(!(w->herois = malloc(w->n_herois * sizeof(struct heroi *)))){
        free(w);
        return NULL;
    }

    /*tenta alocar vetor de bases*/
    if(!(w->bases = malloc(w->n_bases * sizeof(struct base *)))){
        free(w->herois);
        free(w);
        return NULL;
    }

    /*tenta alocar vetor de missoes*/
    if(!(w->missoes = malloc(w->n_missoes * sizeof(struct missao *)))){
        free(w->herois);
        free(w->bases);
        free(w);
        return NULL;
    }

    /*inicializa os herois*/
    for(i=0;i < w->n_herois;i++)
        inicializa_heroi(w,i);

    /*inicializa as bases*/
    for(i=0;i < w->n_bases;i++)
        inicializa_base(w,i);

    /*inicializa as missoes*/
    for(i=0;i < w->n_missoes;i++)
        inicializa_missao(w,i);

    w->relogio = T_INICIO;
    w->LEF = fprio_cria(); /*cria LEF*/

    return w;
}