#ifndef EVENTOS
#define EVENTOS

#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7 
#define MORRE 8
#define MISSAO 9
#define FIM 10

#include "entidades.h"

struct chega{
    int tempo;
    int heroi;
    int base;
};

struct espera{
    int tempo;
    int heroi;
    int base;
};

struct desiste{
    int tempo;
    int heroi;
    int base;
};

struct avisa{
    int tempo;
    int base;
};

struct entra{
    int tempo;
    int heroi;
    int base;
};

struct sai{
    int tempo;
    int heroi;
    int base;
};

struct viaja{
    int tempo;
    int heroi;
    int destino;
};

struct morre{
    int tempo;
    int heroi;
    int base;
};

struct ev_missao{
    int tempo;
    int mis;
};

struct fim{
    int tempo;
};

int evento_chega(struct mundo *w, struct heroi *h, struct base *b);

int evento_espera(struct mundo *w, struct heroi *h, struct base *b);

int evento_desiste(struct mundo *w, struct heroi *h);

int evento_avisa(struct mundo *w, struct base *b);

int evento_entra(struct mundo *w, struct heroi *h, struct base *b);

int evento_sai(struct mundo *w, struct heroi *h, struct base *b);

int evento_viaja(struct mundo *w, struct heroi *h, struct base *d);

int evento_morre(struct mundo *w, struct heroi *h, struct base *b);

int evento_missao(struct mundo *w, struct missao *m);

int evento_fim(struct mundo *w);

int agenda_eventos(struct mundo *w);

#endif