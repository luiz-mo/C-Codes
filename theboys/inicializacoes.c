#include "inicializacoes.h"
#include "conjunto.h"
#include "entidades.h"


/*retorna um numero aleatorio no intervalo de min ate max*/
int aleat(int min, int max){
    return min+rand()%(max-min+1);
}

int inicializa_heroi(struct mundo *w, int id){
    struct heroi *h;
    int i, hab, cap;

    if(!(h = malloc(sizeof(struct heroi))))
        return 0;
    
    h->id = id;

    h->experiencia = 0;
    h->paciencia = aleat(P_MIN,P_MAX);
    h->velocidade = aleat(V_MIN,V_MAX);
    h->vivo = 1; 
    
    cap = aleat(HAB_MIN,HAB_MAX);
    h->habilidades = cjto_cria(cap);
    for(i=0;i < cap;i++){
        hab = aleat(0,w->n_habilidades-1);
        cjto_insere(h->habilidades,hab);
    }

    w->herois[id] = h;

    return 1;
}

int inicializa_base(struct mundo *w, int id){
    struct base *b;

    if(!(b = malloc(sizeof(struct base))))
        return 0;

    b->id = id; 

    b->local.x = aleat(COORD_MIN,COORD_MAX);
    b->local.y = aleat(COORD_MIN,COORD_MAX);

    b->lotacao = aleat(LOT_MIN,LOT_MAX);
    b->presentes = cjto_cria(w->n_herois);
    b->fila_espera = lista_cria();
    b->habilidades = cjto_cria(w->n_habilidades);

    w->bases[id] = b;

    return 1;
}

int inicializa_missao(struct mundo *w, int id){
    struct missao *m;
    int cap, i, hab;

    if(!(m = malloc(sizeof(struct missao))))
        return 0;

    m->id = id;
    m->cumprida = 0;

    m->local.x = aleat(COORD_MIN,COORD_MAX);
    m->local.y = aleat(COORD_MIN,COORD_MAX);
    
    cap = aleat(HAB_N_MIN,HAB_N_MAX);
    m->habilidades = cjto_cria(cap);
    for(i=0;i < cap;i++){
        hab = aleat(0,w->n_habilidades-1);
        cjto_insere(m->habilidades,hab);
    }

    w->missoes[id] = m;

    return 1;
}

struct mundo * inicializa_mundo(){
    struct mundo *w;
    int i;

    w->n_bases = N_BASES;
    w->n_herois = N_HEROIS;
    w->n_missoes = N_MISSOES;
    w->n_habilidades = N_HABILIDADES;
    w->n_compostosV = N_COMPOSTOS_V;

    if(!(w = malloc(sizeof(struct mundo))))
        return NULL;

    for(i=0;i < w->n_herois;i++)
        inicializa_heroi(w,i);

    for(i=0;i < w->n_bases;i++)
        inicializa_base(w,i);

    for(i=0;i < w->n_missoes;i++)
        inicializa_missao(w,i);

    w->relogio = T_INICIO;
    w->LEF = fprio_cria();

    return w;
}