#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fprio.h"
#include "lista.h"
#include "eventos.h"
#include "inicializacoes.h"

int calculo_distancia(struct coord c1, struct coord c2){
    int deltaX, deltaY;

    deltaX = c2.x - c1.x;
    deltaY = c2.y - c1.y;

    /*como sqrt retorna double, tem que converter para int*/
    return  sqrt(deltaX * deltaX + deltaY*deltaY);
}

void Particao(struct mundo *w, struct missao *m, int v[], int ini, int fim, int *pos_pivo){
    int i, j, pivo, aux, dist_pivo, dist_i, dist_j;
    *pos_pivo = ini;
    pivo = v[*pos_pivo];
    i = ini+1;
    j = fim;

    dist_pivo = calculo_distancia(w->bases[v[*pos_pivo]]->local, m->local);

    while(i<=j){
        dist_i = calculo_distancia(w->bases[v[i]]->local, m->local);

        while(i<=fim && dist_i <= dist_pivo){
            i++;
            /*atualiza o dist_i*/
            if(i<=fim)
                dist_i = calculo_distancia(w->bases[v[i]]->local, m->local);
        }

        dist_j = calculo_distancia(w->bases[v[j]]->local, m->local);
        while(j>ini && dist_j> dist_pivo){
            j--;
            if(j>ini)
            dist_j = calculo_distancia(w->bases[v[j]]->local, m->local);
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

int evento_chega(struct mundo *w, struct chega *ev){
    struct heroi *h = w->herois[ev->heroi];
    struct base *b = w->bases[ev->base];
    int espera;

    if(!(h->vivo))
        return 0;

    h->base = b->id;   

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

    destino = aleat(0,w->n_bases-1); /*numero de 0 a n_bases-1*/

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

    destino = aleat(0,w->n_bases-1);

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

    distancia = calculo_distancia(w->bases[h->base]->local,d->local);
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
    h->base = -1;
    h->vivo = 0;
    w->herois_mortos++;

    printf("%6d: MORRE HEROI %2d MISSAO %d\n",ev->tempo,h->id,ev->mis);

    if(!(novo_ev = malloc(sizeof(struct avisa))))
        return 0;

    novo_ev->tempo = ev->tempo;
    novo_ev->base = b->id;

    fprio_insere(w->LEF,novo_ev,AVISA,novo_ev->tempo);

    return 1;
}

int evento_missao(struct mundo *w, struct ev_missao *ev){
    int BMP, i,j;
    int v[N_BASES]; /*vetor com os ids das bases*/
    struct missao *m = w->missoes[ev->missao];
    struct cjto_t *hab_base;

    m->tentativas++;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ",ev->tempo,m->id,m->tentativas);
    cjto_imprime(m->habilidades);
    printf(" ]\n");

    /*inicializa o vetor*/
    for(i=0;i < w->n_bases;i++)
        v[i] = i;

    /*ordena o vetor de acordo com a distancia de cada base ate a missao*/
    QuickSort(w,m,v,0,w->n_bases-1);

    /*inicializa BMP com -1 para usar como flag*/
    BMP = -1;

    /*percorre o vetor ordenado verificando se a base cumpre os requisitos da missao*/
    for(i=0;i < w->n_bases;i++){
        struct base *b = w->bases[v[i]];

        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS: [ ",ev->tempo,m->id,b->id,calculo_distancia(m->local,b->local));
        cjto_imprime(b->presentes);
        printf(" ]\n");

        hab_base = cjto_cria(w->n_habilidades);

        for(j=0;j < w->n_herois;j++){
            if(cjto_pertence(b->presentes,j)){

            printf("%6d: MISSAO %d HAB HEROI %2d: [ ",ev->tempo,m->id,w->herois[j]->id);
            cjto_imprime(w->herois[j]->habilidades);
            printf(" ]\n");

            struct cjto_t *temp = cjto_uniao(hab_base,w->herois[j]->habilidades);
            cjto_destroi(hab_base);
            hab_base = temp;
            }
        }

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ",ev->tempo,m->id,w->bases[v[i]]->id);
        cjto_imprime(hab_base);
        printf(" ]\n");

        if(cjto_contem(hab_base,m->habilidades)){
            BMP = v[i];
            break;
        }

        cjto_destroi(hab_base);
        hab_base = NULL;
    }

    /*se achou BMP, marca missao como cumprida e incrementa xp dos herois dessa base*/
    if(BMP >= 0){

        m->cumprida = 1;
        w->bases[BMP]->missoes_feitas++;
        w->missoes_cumpridas++;

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ",ev->tempo,m->id,BMP);
        cjto_imprime(hab_base);
        printf(" ]\n");

        for(i=0;i < w->n_herois;i++)
            if(cjto_pertence(w->bases[BMP]->presentes,i))
                w->herois[i]->experiencia++;

        cjto_destroi(hab_base);
        
        return 1;
    }

    /*quando nao achou BMP, verifica possibilidade de usar compostoV*/
    if(w->n_compostosV > 0 && ev->tempo % 2500 == 0){
        int baseMaisProx, idMaisXp, maiorXp, achou;
        idMaisXp = -1;
        maiorXp = -1;
        baseMaisProx = v[0];
        achou = 0; /*flag para saber se achou heroi com mais xp na base*/

        for(i=0;i < w->n_herois;i++){
            if(cjto_pertence(w->bases[baseMaisProx]->presentes, i))
                if(w->herois[i]->experiencia > maiorXp){
                    idMaisXp = i;
                    maiorXp = w->herois[i]->experiencia;
                    achou = 1;
                }
        }

        /*se achou o heroi, conclui a missao, senao vai para o ultimo caso*/
        if(achou){
            struct cjto_t *hab_base = cjto_cria(w->n_habilidades);
            w->n_compostosV--;
            m->cumprida = 1;
            w->bases[baseMaisProx]->missoes_feitas++;
            w->missoes_cumpridas++;

            for(j=0;j < w->n_herois;j++){
                if(cjto_pertence(w->bases[baseMaisProx]->presentes,j)){
                    struct cjto_t *temp = cjto_uniao(hab_base,w->herois[j]->habilidades);
                    cjto_destroi(hab_base);
                    hab_base = temp;
            }
        }

            printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ",ev->tempo,m->id,baseMaisProx);
            cjto_imprime(hab_base);
            printf(" ]\n");
            
            /*incrementa xp dos herois da mesma base do heroi que tomou o compostoV*/
            for(i=0;i < w->n_herois;i++)
                if(i != idMaisXp && cjto_pertence(w->bases[baseMaisProx]->presentes,i))
                    w->herois[i]->experiencia++;


            struct morre *evento;

            if(!(evento = malloc(sizeof(struct morre))))
                return 0;

            evento->tempo = ev->tempo;
            evento->base = baseMaisProx;
            evento->heroi = idMaisXp;
            evento->mis = m->id;
                
            fprio_insere(w->LEF,evento,MORRE,evento->tempo);

            cjto_destroi(hab_base);

            return 1;
        }
    }
    
    /*reagenda missao para o proximo dia*/
    struct ev_missao *novo_ev;

    if(!(novo_ev = malloc(sizeof(struct ev_missao))))
        return 0;

    printf("%6d: MISSAO %d IMPOSSIVEL\n",ev->tempo,m->id);

    novo_ev->tempo = ev->tempo + 24*60; /*agenda missao para o dia seguinte*/
    novo_ev->missao = m->id;
    fprio_insere(w->LEF,novo_ev,MISSAO,novo_ev->tempo);

    return 1;
}

int evento_fim(struct mundo *w){
    struct base *b;
    struct heroi *h;
    int i, id_menos_tent, id_mais_tent;
    float tx_missoes, tx_mortalidade, media_tent;

    printf("%6d: FIM\n",w->relogio);
    printf("\nEstatísticas:\n");

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
    
    if(w->n_missoes != 0){
        tx_missoes = 100.0 * w->missoes_cumpridas/w->n_missoes; /*taxa de missoes cumpridas*/

        printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n",w->missoes_cumpridas,w->n_missoes,tx_missoes);
    }

    /*acha id da missao com mais e menos tentaivas e calcula media*/
    id_menos_tent = 0;
    id_mais_tent = 0;
    media_tent = 0;
    for(i=0;i < w->n_missoes;i++){
        if(w->missoes[i]->tentativas > w->missoes[id_mais_tent]->tentativas)
            id_mais_tent = i;
        else if(w->missoes[i]->tentativas < w->missoes[id_menos_tent]->tentativas)
            id_menos_tent = i;
        
        media_tent += w->missoes[i]->tentativas;
    }

    if(w->n_missoes != 0){
        media_tent /= w->n_missoes;

        printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",w->missoes[id_menos_tent]->tentativas,w->missoes[id_mais_tent]->tentativas,media_tent);
    }

    if(w->n_herois != 0){
        tx_mortalidade = 100.0 * w->herois_mortos/w->n_herois;

        printf("TAXA MORTALIDADE: %.1f%%\n",tx_mortalidade);
    }

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