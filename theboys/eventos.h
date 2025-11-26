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
    int mis;
};

struct ev_missao{
    int tempo;
    int missao;
};

struct fim{
    int tempo;
};

int evento_chega(struct mundo *w, struct chega *ev);

int evento_espera(struct mundo *w, struct espera *ev);

int evento_desiste(struct mundo *w, struct desiste *ev);

int evento_avisa(struct mundo *w, struct avisa *ev);

int evento_entra(struct mundo *w, struct entra *ev);

int evento_sai(struct mundo *w, struct sai *ev);

int evento_viaja(struct mundo *w, struct viaja *ev);

int evento_morre(struct mundo *w, struct morre *ev);

/*int evento_missao(struct mundo *w, struct ev_missao *ev);
*/
int evento_fim(struct mundo *w);

int agenda_eventos(struct mundo *w);

#endif