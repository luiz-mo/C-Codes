#ifndef ENTIDADES
#define ENTIDADES

#include "conjunto.h"
#include "lista.h"
#include "fprio.h"

struct coord{
    int x;
    int y;
};

struct heroi{
    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
    int vivo; /*1 se vivo, 0 se morto*/
};

struct base{
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct lista *fila_espera;
    struct coord local;
    int max_espera; /*maior tamanho que a fila de espera teve*/
    int missoes_feitas;
};

struct missao{
    int id;
    struct cjto_t *habilidades;
    struct coord local;
    int cumprida; /*1 se cumprida, 0 caso contrario*/
    int tentativas;
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
    struct fprio_t *LEF;
    int eventos_tratados;
    int herois_mortos;
    int missoes_cumpridas;
};

#endif