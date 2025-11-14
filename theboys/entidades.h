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