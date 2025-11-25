#ifndef ENTIDADES
#define ENTIDADES

#include "conjunto.h"
#include "lista.h"
#include "fila.h"
#include "fprio.h"

struct heroi{
    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
    int vivo; /*1 se vivo, 0 se morto*/
};

struct coord{
    int x;
    int y;
};

struct base{
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct lista *fila_espera;
    struct coord local;
};

struct missao{
    int id;
    struct cjto_t *habilidades;
    struct coord local;
    int cumprida; /*1 se cumprida, 0 caso contrario*/
};

struct mundo{
    int n_herois;
    struct heroi **herois;
    int n_bases;
    struct base **bases;
    int n_missoes;
    struct missao **missoes;
    int n_habilidades;
    int n_compostosV;
    struct coord tam;
    int relogio;    
    struct fprio *LEF;
};

#endif