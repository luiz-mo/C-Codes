// programa principal do projeto "The Boys - 2025/2"
// Autor: Luiz Guilherme de Souza Mo, GRR 20252981

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "conjunto.h"
#include "lista.h"
#include "fila.h"
#include "fprio.h"
#include "entidades.h"
#include "inicializacoes.h"
#include "eventos.h"

void destroi_mundo(struct mundo **w){
    int i;
    if(!*w)
        return;

    /*libera herois*/
    for(i=0;i < (*w)->n_herois;i++){
        struct heroi *h = (*w)->herois[i];
        h->habilidades = cjto_destroi(h->habilidades);
        free(h);
    }
    free((*w)->herois);

    /*libera bases*/
    for(i=0;i < (*w)->n_bases;i++){
        struct base *b = (*w)->bases[i];
        b->presentes = cjto_destroi(b->presentes);
        lista_destroi(&b->fila_espera);
        free(b);
    }
    free((*w)->bases);

    /*libera missoes*/
    for(i=0;i < (*w)->n_missoes;i++){
        struct missao *m = (*w)->missoes[i];
        m->habilidades = cjto_destroi(m->habilidades);
        free(m);
    }
    free((*w)->missoes);

    fprio_destroi((*w)->LEF);
    free((*w));
    *w = NULL;
}

// programa principal
int main (){
    struct mundo *w;
    void *evento;
    int tipo, tempo, fim;
    srand(time(NULL));

    w = inicializa_mundo();
    if(!w)
        return 1; /*encerra execucao com erro*/

    agenda_eventos(w);
    fim = 0;

    while(!fim){
        evento = fprio_retira(w->LEF,&tipo,&tempo);
        w->relogio = tempo;
        w->eventos_tratados++;
        switch(tipo){
            case CHEGA:
                evento_chega(w,evento);
                break;
            case ESPERA:
                evento_espera(w,evento);
                break;
            case DESISTE:
                evento_desiste(w,evento);
                break;
            case AVISA:
                evento_avisa(w,evento);
                break;
            case ENTRA:
                evento_entra(w,evento);
                break;
            case SAI:
                evento_sai(w,evento);
                break;
            case VIAJA:
                evento_viaja(w,evento);
                break;
            case MORRE:
                evento_morre(w,evento);
                break;
            case MISSAO:
                evento_missao(w,evento);
                break;
            case FIM:
                evento_fim(w);
                fim = 1;
        }
        free(evento);
    }
    
    destroi_mundo(&w);

    return 0;
}

