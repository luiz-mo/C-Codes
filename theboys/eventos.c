#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fprio.h"
#include "lista.h"
#include "eventos.h"

int calculo_distancia(struct base *b1, struct base *b2){
    int deltaX, deltaY;
    deltaX = b2->local.x - b1->local.x;
    deltaY = b2->local.y - b1->local.y;
    return sqrt(deltaX * deltaX + deltaY*deltaY);
}

int evento_chega(struct mundo *w, struct heroi *h, struct base *b){
    int espera;
    h->base = b->id;

    if(!(h->vivo))
        return 0;

    if(b->presentes->num < b->lotacao && lista_vazia(b->fila_espera))
        espera = 1;
    else
        espera = h->paciencia > (10 * lista_tamanho(b->fila_espera));

    
    
    if(espera){
        struct espera *evento;

        if(!(evento = malloc(sizeof(struct espera))))
            return 0;

        evento->tempo = w->relogio;
        evento->heroi = h->id;
        evento->base = b->id;

        fprio_insere(w->LEF,evento,ESPERA,evento->tempo);

        return 1;
    }

    struct desiste *evento;
    
    if(!(evento = malloc(sizeof(struct desiste))))
        return 0;

    evento->tempo = w->relogio;
    evento->heroi = h->id;
    evento->base = b->id;

    fprio_insere(w->LEF,evento,DESISTE,evento->tempo);
    
    return 1;
}

int evento_espera(struct mundo *w, struct heroi *h, struct base *b){
    struct avisa *evento;

    if(!(h->vivo))
        return 0;

    lista_insere_fim(b->fila_espera,h->id);

    if(!(evento = malloc(sizeof(struct avisa))))
        return 0;

    evento->base = b->id;
    evento->tempo = w->relogio;

    fprio_insere(w->LEF,evento,AVISA,evento->tempo);

    return 1;
}

int evento_desiste(struct mundo *w, struct heroi *h){
    struct viaja *evento;
    int destino;

    if(!(h->vivo))
        return 0;

    destino = rand()%w->n_bases + 1; /*numero de 0 a n_bases*/

    if(!(evento = malloc(sizeof(struct viaja))))
        return 0;

    evento->tempo = w->relogio;
    evento->heroi = h->id;
    evento->destino = destino;

    fprio_insere(w->LEF,evento,VIAJA,evento->tempo);

    return 1;
}

int evento_avisa(struct mundo *w, struct base *b){
    struct entra *evento;
    int id; /*id do heroi que vai entrar na base*/

    if(!(evento = malloc(sizeof(struct entra))))
        return 0;

    while(cjto_card(b->presentes) <= b->lotacao && !(lista_vazia(b->fila_espera))){
        lista_remove_inicio(b->fila_espera,&id);
        if(!(w->herois[id]->vivo))
            continue;

        cjto_insere(b->presentes,id);

        evento->tempo = w->relogio;
        evento->base = b->id;
        evento->heroi = id;

        fprio_insere(w->LEF,evento,ENTRA,evento->tempo);
    }

    return 1;
}

int evento_entra(struct mundo *w, struct heroi *h, struct base *b){
    struct sai *evento;
    int TPB; /*tempo de permanencia na base*/

    if(!(h->vivo))
        return 0;

    if(!(evento = malloc(sizeof(struct sai))))
        return 0;

    TPB = 15 + h->paciencia * (1+rand() % 20); /*aleatorio de 1 a 20*/

    evento->tempo = w->relogio + TPB;
    evento->heroi = h->id;
    evento->base = b->id;

    fprio_insere(w->LEF,evento,SAI,evento->tempo);

    return 1;
}

int evento_sai(struct mundo *w, struct heroi *h, struct base *b){
    struct viaja *evento1;
    struct avisa *evento2;
    int destino;

    if(!(h->vivo))
        return 0;

    cjto_retira(b->presentes,h->id);

    destino = rand() % w->n_bases+1;

    if(!(evento1 = malloc(sizeof(struct viaja))))
        return 0;

    if(!(evento2 = malloc(sizeof(struct avisa))))
        return 0;

    evento1->tempo = w->relogio;
    evento1->destino = destino;
    evento1->heroi = h->id;

    fprio_insere(w->LEF,evento1,VIAJA,evento1->tempo);

    evento2->tempo = w->relogio;
    evento2->base = b->id;

    fprio_insere(w->LEF,evento2,AVISA,evento2->tempo);

    return 1;
}

int evento_viaja(struct mundo *w, struct heroi *h, struct base *d){
    struct chega *evento;
    int duracao, distancia;

    if(!(h->vivo))
        return 0;

    distancia = calculo_distancia(h->base,d);
    duracao = distancia / h->velocidade;

    if(!(evento = malloc(sizeof(struct chega))))
        return 0;

    evento->tempo = w->relogio + duracao;
    evento->base = d->id;

    fprio_insere(w->LEF,evento,VIAJA,evento->tempo);
}

int evento_morre(struct mundo *w, struct heroi *h, struct base *b){
    struct avisa *evento;

    if(!(h->vivo))
        return 0;

    cjto_retira(b->presentes,h->id);
    h->vivo = 0;

    if(!(evento = malloc(sizeof(struct avisa))))
        return 0;

    evento->tempo = w->relogio;
    evento->base = b;

    fprio_insere(w->LEF,evento,AVISA,evento->tempo);

    return 1;
}

int evento_missao(struct mundo *w, struct heroi *h, struct base *b){
    
}

int evento_fim(struct mundo *w){

}