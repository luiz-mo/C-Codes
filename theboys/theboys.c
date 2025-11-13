// programa principal do projeto "The Boys - 2025/2"
// Autor: Luiz Guilherme de Souza Mo, GRR 20252981

#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"
#include "lista.h"
#include "fila.h"
#include "fprio.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES*5)
#define N_BASES (N_HEROIS/5)
#define N_MISSOES (T_FIM_DO_MUNDO/100)
#define N_COMPOSTOS_V (N_HABILIDADES*3)

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
    struct coord coord_base;
};

struct missao{
    int id;
    struct cjto_t *habilidades;
    struct coord local;
};

struct mundo{
    int n_herois[N_HEROIS];
    struct heroi *herois;
    int n_bases[N_BASES];
    struct base *bases;
    int n_missoes[N_MISSOES];
    struct missao *missoes;
    int n_habilidades[N_HABILIDADES];
    int n_compostosV[N_COMPOSTOS_V];
    struct coord tam[N_TAMANHO_MUNDO];
    int relogio[T_INICIO];
};



// programa principal
int main ()
{
    srand(0);

  // executar o laço de simulação
  
  // destruir o mundo

  return (0) ;
}

