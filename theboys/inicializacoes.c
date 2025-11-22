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
    int i, hab, cap;

    if(!(h = malloc(sizeof(struct heroi))))
        return 0;
    
    h->id = id;

    h->experiencia = 0;
    h->paciencia = P_MIN + rand()%(P_MAX-P_MIN+1);
    h->velocidade = V_MIN + rand()%(V_MAX-V_MIN+1);
    h->vivo = 1; 
    
    cap = HAB_MIN + rand()%(HAB_MAX-HAB_MIN+1);
    h->habilidades = cjto_cria(cap);
    for(i=0;i < cap;i++){
        hab = 1  + rand()%(N_HABILIDADES+1);
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

    b->local.x = COORD_MIN + rand()%(COORD_MAX-COORD_MIN+1);
    b->local.y = COORD_MIN + rand()%(COORD_MAX-COORD_MIN+1);

    b->lotacao = LOT_MIN + rand()%(LOT_MAX-LOT_MIN+1);
    b->presentes = cjto_cria(0);
    b->fila_espera = lista_cria();

    w->bases[id] = b;

    return 1;
}

int inicializa_missao(struct mundo *w, int id){
    struct missao *m;
    int cap, i, hab;

    if(!(m = malloc(sizeof(struct missao))))
        return 0;

    m->id = id;

    m->local.x = COORD_MIN + rand()%(COORD_MAX-COORD_MIN+1);
    m->local.y = COORD_MIN + rand()%(COORD_MAX-COORD_MIN+1);
    
    cap = HAB_N_MIN + rand()%(HAB_N_MAX-HAB_N_MIN+1);
    m->habilidades = cjto_cria(cap);
    for(i=0;i < cap;i++){
        hab = 1  + rand()%(N_HABILIDADES+1);
        cjto_insere(m->habilidades,hab);
    }

    w->missoes[id] = m;

    return 1;
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

    w->relogio = T_INICIO;
    w->LEF = fprio_cria();

    return 1;
}