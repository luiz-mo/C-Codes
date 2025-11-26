#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fprio.h"
#include "lista.h"
#include "eventos.h"
#include "inicializacoes.h"

void Particao(struct mundo *w, struct missao *m, int v[], int ini, int fim, int *pos_pivo){
    int i, j, pivo, aux, dist_pivo, dist_i, dist_j;
    *pos_pivo = ini;
    pivo = v[*pos_pivo];
    i = ini+1;
    j = fim;

    dist_pivo = calculo_distancia(&w->bases[v[*pos_pivo]]->local, &m->local);

    while(i<=j){
        dist_i = calculo_distancia(&w->bases[v[i]]->local, &m->local);

        while(i<=fim && dist_i <= dist_pivo){
            i++;
            /*atualiza o dist_i*/
            if(i<=fim)
                dist_i = calculo_distancia(&w->bases[v[i]]->local, &m->local);
        }

        dist_j = calculo_distancia(&w->bases[v[j]]->local, &m->local);
        while(j>ini && dist_j> dist_pivo){
            j--;
            if(j>ini)
            dist_j = calculo_distancia(&w->bases[v[j]]->local, &m->local);
        }
        if(i<j){
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }
    v[ini] = v[j];
    v[j] = pivo;
    *pos_pivo = j;
}

void QuickSort(struct mundo *w, struct missao *m, int v[], int ini, int fim){
    int pos_pivo;
    if(ini<fim){
        Particao(w,m,v,ini,fim,&pos_pivo);
        QuickSort(w,m,v,ini,pos_pivo - 1);
        QuickSort(w,m,v, pos_pivo+1, fim);
    }
}

int encontra_BMP(struct mundo *w, struct missao *m){
    int v[w->n_bases]; /*vetor com os ids das bases*/
    int i, j;

    /*inicializa o vetor com os ids das bases*/
    for(i=0;i < w->n_bases;i++)
        v[i] = w->bases[i]->id;

    QuickSort(w,m,v,0,w->n_bases);

    /*percorre o vetor ordenado verificando se a base cumpre os requisitos da missao*/
    for(i=0;i < w->n_bases;i++){
        struct base *b = w->bases[v[i]];

        struct cjto_t *hab_base;
        hab_base = cjto_cria(w->n_habilidades);

        for(j=0;j < cjto_card(b->presentes);j++)
            cjto_uniao(hab_base,w->herois[j]->habilidades);

        if(cjto_iguais(hab_base,m->habilidades))
            return i;
    }

    /*se chegou aqui, significa que nao achou BMP e retorna -1 como flag*/
    return -1;
}

void imprimir_lista (struct lista *l){
    int chave;

    if (lista_vazia (l)){
        printf (" ");
        return;
    }

    lista_inicia_iterador (l);
    lista_incrementa_iterador (l, &chave);
    printf ("%2d", chave);
    while (lista_incrementa_iterador (l, &chave))
        printf (" %2d", chave);
}


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

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n",ev->tempo,h->id,b->id,cjto_card(b->presentes),b->lotacao);

        novo_ev->tempo = ev->tempo;
        novo_ev->heroi = h->id;
        novo_ev->base = b->id;

        fprio_insere(w->LEF,novo_ev,ESPERA,novo_ev->tempo);

        return 1;
    }

    struct desiste *novo_ev;
    
    if(!(novo_ev = malloc(sizeof(struct desiste))))
        return 0;

    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n",ev->tempo,h->id,b->id,cjto_card(b->presentes),b->lotacao);

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

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",ev->tempo,h->id,b->id,lista_tamanho(b->fila_espera));

    if(lista_tamanho(b->fila_espera) > b->max_espera)
        b->max_espera = lista_tamanho(b->fila_espera);

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

    printf("%6d: DESIST HEROI %2d BASE %d\n",ev->tempo,h->id,b->id);

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

    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ",ev->tempo,b->id,cjto_card(b->presentes),b->lotacao);
    imprimir_lista(b->fila_espera);
    printf(" ]\n");

    while(cjto_card(b->presentes) < b->lotacao && !(lista_vazia(b->fila_espera))){
        lista_remove_inicio(b->fila_espera,&id);
        if(!(w->herois[id]->vivo))
            continue;

        cjto_insere(b->presentes,id);

        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n",ev->tempo,b->id,id);

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

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n",ev->tempo,h->id,b->id,cjto_card(b->presentes),b->lotacao,ev->tempo+TPB);

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

    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n",ev->tempo,h->id,b->id,cjto_card(b->presentes),b->lotacao);

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

    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",ev->tempo,h->id,h->base,d->id,distancia,h->velocidade,ev->tempo+duracao);

    if(!(novo_ev = malloc(sizeof(struct chega))))
        return 0;

    novo_ev->tempo = ev->tempo + duracao;
    novo_ev->heroi = h->id;
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

    printf("%6d: MORRE HEROI %2d MISSAO %d\n",ev->tempo,h->id,ev->mis);

    if(!(novo_ev = malloc(sizeof(struct avisa))))
        return 0;

    novo_ev->tempo = ev->tempo;
    novo_ev->base = b->id;

    fprio_insere(w->LEF,novo_ev,AVISA,novo_ev->tempo);

    return 1;
}

int evento_missao(struct mundo *w, struct ev_missao *ev){
    int BMP, i, idMaisXP, baseMaisXp; 
    struct missao *m = w->missoes[ev->missao];

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ",ev->tempo,m->id,m->tentativas);
    cjto_imprime(m->habilidades);
    printf(" ]\n");

    BMP = encontra_BMP(w,m);

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
        evento->missao = m->id;
        fprio_insere(w->LEF,evento,MISSAO,evento->tempo);
    }
}

int evento_fim(struct mundo *w){
    struct base *b;
    struct heroi *h;
    int i;

    for(i=0;i < w->n_herois;i++){
        h = w->herois[i];

        printf("HEROI %2d %5s PAC %3d VEL %4d EXP %4d HABS [ ",h->id,h->vivo? "VIVO" : "MORTO",h->paciencia,h->velocidade,h->experiencia);
        cjto_imprime(h->habilidades);
        printf(" ]\n");
    }

    for(i=0;i < w->n_bases;i++){
        b = w->bases[i];

        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",b->id,b->lotacao,b->max_espera,b->missoes_feitas);
    }

    printf("EVENTOS TRATADOS: %d\n",w->eventos_tratados);

    return 1;
}

int agenda_eventos(struct mundo *w){
    int i;
    
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
        evento->missao = i;

        fprio_insere(w->LEF,evento,MISSAO,evento->tempo);
    }

    struct fim *evento;

    if(!(evento = malloc(sizeof(struct fim))))
        return 0;

    evento->tempo = T_FIM_DO_MUNDO;

    fprio_insere(w->LEF,evento,FIM,evento->tempo);

    return 1;
}