#ifndef ENTIDADES
#define ENTIDADES

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES*5)
#define N_BASES (N_HEROIS/5)
#define N_MISSOES (T_FIM_DO_MUNDO/100)
#define N_COMPOSTOS_V (N_HABILIDADES*3)

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
};

struct coord{
    int x;
    int y;
};

struct base{
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *fila_herois;
    struct coord local;
};

struct missao{
    int id;
    struct cjto_t *habilidades;
    struct coord local;
};

struct mundo{
    int n_herois;
    struct heroi *herois;
    int n_bases;
    struct base *bases;
    int n_missoes;
    struct missao *missoes;
    int n_habilidades;
    int n_compostosV;
    struct coord tam;
    int relogio;
};

#endif