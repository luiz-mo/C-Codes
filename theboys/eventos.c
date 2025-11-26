#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fprio.h"
#include "lista.h"
#include "eventos.h"
#include "inicializacoes.h"

int calculo_distancia(struct coord *c1, struct coord *c2){
    int deltaX, deltaY;
    deltaX = c2->x - c1->x;
    deltaY = c2->y - c1->y;
    return sqrt(deltaX * deltaX + deltaY*deltaY);
}

int evento_chega(struct mundo *w, struct chega *ev){
    struct heroi *h = w->herois[ev->heroi];
    struct base *b = w->bases[ev->base];
    int espera;
    h->base = b->id;

    if(!(h->vivo))
        return 0;

    if(cjto_card(b->presentes) < b->lotacao && lista_vazia(b->fila_espera))
        espera = 1;
    else
        espera = h->paciencia > (10 * lista_tamanho(b->fila_espera));

    
    
    if(espera){
        struct espera *novo_ev;

        if(!(novo_ev = malloc(sizeof(struct espera))))
            return 0;

        novo_ev->tempo = ev->tempo;
        novo_ev->heroi = h->id;
        novo_ev->base = b->id;

        fprio_insere(w->LEF,novo_ev,ESPERA,novo_ev->tempo);

        return 1;
    }

    struct desiste *novo_ev;
    
    if(!(novo_ev = malloc(sizeof(struct desiste))))
        return 0;

    novo_ev->tempo = ev->tempo;
    novo_ev->heroi = h->id;
    novo_ev->base = b->id;

    fprio_insere(w->LEF,novo_ev,DESISTE,novo_ev->tempo);
    
    return 1;
}

int evento_espera(struct mundo *w, struct espera *ev){
    struct heroi *h = w->herois[ev->heroi];
    struct base *b = w->bases[ev->base];
    struct avisa *novo_ev;

    if(!(h->vivo))
        return 0;

    lista_insere_fim(b->fila_espera,h->id);

    if(!(novo_ev = malloc(sizeof(struct avisa))))
        return 0;

    novo_ev->base = b->id;
    novo_ev->tempo = ev->tempo;

    fprio_insere(w->LEF,novo_ev,AVISA,novo_ev->tempo);

    return 1;
}

int evento_desiste(struct mundo *w, struct desiste *ev){
    struct heroi *h = w->herois[ev->heroi];
    struct base *b = w->bases[ev->base];
    struct viaja *novo_ev;
    int destino;

    if(!(h->vivo))
        return 0;

    destino = aleat(0,N_BASES-1); /*numero de 0 a n_bases-1*/

    if(!(novo_ev = malloc(sizeof(struct viaja))))
        return 0;

    novo_ev->tempo = ev->tempo;
    novo_ev->heroi = h->id;
    novo_ev->destino = destino;

    fprio_insere(w->LEF,novo_ev,VIAJA,novo_ev->tempo);

    return 1;
}

int evento_avisa(struct mundo *w, struct avisa *ev){
    struct base *b = w->bases[ev->base];
    int id; /*id do heroi que vai entrar na base*/

    while(cjto_card(b->presentes) < b->lotacao && !(lista_vazia(b->fila_espera))){
        lista_remove_inicio(b->fila_espera,&id);
        if(!(w->herois[id]->vivo))
            continue;

        cjto_insere(b->presentes,id);

        struct entra *novo_ev;
        if(!(novo_ev = malloc(sizeof(struct entra))))
            return 0;

        novo_ev->tempo = ev->tempo;
        novo_ev->base = b->id;
        novo_ev->heroi = id;

        fprio_insere(w->LEF,novo_ev,ENTRA,novo_ev->tempo);
    }

    return 1;
}

int evento_entra(struct mundo *w, struct entra *ev){
    struct heroi *h = w->herois[ev->heroi];
    struct base *b = w->bases[ev->base];
    struct sai *novo_ev;
    int TPB; /*tempo de permanencia na base*/

    if(!(h->vivo))
        return 0;

    if(!(novo_ev = malloc(sizeof(struct sai))))
        return 0;

    TPB = 15 + h->paciencia * aleat(1,20); /*aleatorio de 1 a 20*/

    novo_ev->tempo = ev->tempo + TPB;
    novo_ev->heroi = h->id;
    novo_ev->base = b->id;

    fprio_insere(w->LEF,novo_ev,SAI,novo_ev->tempo);

    return 1;
}

int evento_sai(struct mundo *w, struct sai *ev){
    struct heroi *h = w->herois[ev->heroi];
    struct base *b = w->bases[ev->base];
    struct viaja *novo_ev1;
    struct avisa *novo_ev2;
    int destino;

    if(!(h->vivo))
        return 0;

    cjto_retira(b->presentes,h->id);

    destino = aleat(0,N_BASES-1);

    if(!(novo_ev1 = malloc(sizeof(struct viaja))))
        return 0;

    if(!(novo_ev2 = malloc(sizeof(struct avisa))))
        return 0;

    novo_ev1->tempo = ev->tempo;
    novo_ev1->destino = destino;
    novo_ev1->heroi = h->id;

    fprio_insere(w->LEF,novo_ev1,VIAJA,novo_ev1->tempo);

    novo_ev2->tempo = ev->tempo;
    novo_ev2->base = b->id;

    fprio_insere(w->LEF,novo_ev2,AVISA,novo_ev2->tempo);

    return 1;
}

int evento_viaja(struct mundo *w, struct viaja *ev){
    struct heroi *h = w->herois[ev->heroi];
    struct base *d = w->bases[ev->destino]; 
    struct chega *novo_ev;
    int duracao, distancia;

    if(!(h->vivo))
        return 0;

    distancia = calculo_distancia(&w->bases[h->base]->local,&d->local);
    duracao = distancia / h->velocidade;

    if(!(novo_ev = malloc(sizeof(struct chega))))
        return 0;

    novo_ev->tempo = ev->tempo + duracao;
    novo_ev->base = d->id;

    fprio_insere(w->LEF,novo_ev,CHEGA,novo_ev->tempo);

    return 1;
}

int evento_morre(struct mundo *w, struct morre *ev){
    struct heroi *h = w->herois[ev->heroi];
    struct base *b = w->bases[ev->base];
    struct avisa *novo_ev;

    if(!(h->vivo))
        return 0;

    cjto_retira(b->presentes,h->id);
    h->vivo = 0;

    if(!(novo_ev = malloc(sizeof(struct avisa))))
        return 0;

    novo_ev->tempo = w->relogio;
    novo_ev->base = b->id;

    fprio_insere(w->LEF,novo_ev,AVISA,novo_ev->tempo);

    return 1;
}

int evento_missao(struct mundo *w, struct missao *m){
    int BMP, i, idMaisXP, baseMaisXp; 
    BMP = -1;

    for(i=0;i <= w->n_bases;i++){
        if(!(cjto_iguais(m->habilidades,w->bases[i]->habilidades)))
            continue;
        if(calculo_distancia(&m->local,&w->bases[i]->local) < w->bases[BMP]->)
    }
    if(BMP >= 0){
        m->cumprida = 1;
        for(i=0;i < w->n_herois;i++)
            if(cjto_pertence(w->bases[BMP],w->herois[i]))
                w->herois[i]->experiencia++;
    }
    else if(w->n_compostosV > 0 && w->relogio % 2500 == 0){
        idMaisXP = 0; /*id do heroi com mais xp, inicia no heroi 0*/
        baseMaisXp = w->herois[idMaisXP]->base; /*guarda a base do heroi de mais xp*/

        w->n_compostosV--;
        m->cumprida = 1;
        
        /*encontra o heroi com mais experiencia para usar o compostoV e sua base para incrementar a experiencia*/
        for(i=1;i < w->n_herois;i++)
            if(w->herois[i]->experiencia > w->herois[idMaisXP]->experiencia){
                idMaisXP = i;
                baseMaisXp = w->herois[idMaisXP]->base;
            }
        
        /*incrementa xp dos herois da mesma base do heroi que tomou o compostoV*/
        for(i=0;i < w->n_herois;i++)
            if(cjto_pertence(w->bases[baseMaisXp],w->herois[i]))
                w->herois[i]->experiencia++;

        struct morre *evento;

        if(!(evento = malloc(sizeof(struct morre))))
            return 0;

        evento->tempo = w->relogio;
        evento->base = baseMaisXp;
        evento->heroi = idMaisXP;
            
        fprio_insere(w->LEF,evento,MORRE,evento->tempo);
    }
    else{
        struct ev_missao *evento;

        if(!(evento = malloc(sizeof(struct missao))))
            return 0;

        evento->tempo = w->relogio + 24*60; /*agenda missao para o dia seguinte*/
        evento->mis = m->id;
        fprio_insere(w->LEF,evento,MISSAO,evento->tempo);
    }
}

int evento_fim(struct mundo *w){

}

int agenda_eventos(struct mundo *w){
    int i, base, tempo;
    
    for(i=0;i < w->n_herois;i++){
        struct chega *evento;

        if(!(evento = malloc(sizeof(struct chega))))
            return 0;

        evento->base = aleat(0,w->n_bases-1);
        evento->heroi = i;
        evento->tempo = aleat(0,4320); /*4320 = 3 dias*/

        fprio_insere(w->LEF,evento,CHEGA,evento->tempo);
    }

    for(i=0;i < w->n_missoes;i++){
        struct ev_missao *evento;

        if(!(evento = malloc(sizeof(struct ev_missao))))
            return 0;

        evento->tempo = aleat(0,T_FIM_DO_MUNDO);
        evento->mis = i;

        fprio_insere(w->LEF,evento,MISSAO,evento->tempo);
    }

    struct fim *evento;

    if(!(malloc(sizeof(struct fim))))
        return 0;

    evento->tempo = T_FIM_DO_MUNDO;

    fprio_insere(w->LEF,evento,FIM,evento->tempo);

    return 1;
}