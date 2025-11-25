#ifndef INICIALIZACOES
#define INICIALIZACOES

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES*5)
#define N_BASES (N_HEROIS/5)
#define N_MISSOES (T_FIM_DO_MUNDO/100)
#define N_COMPOSTOS_V (N_HABILIDADES*3)

/*defines dos minimos e maximo para usar como intervalo para gerar os numeros aleatorios*/
#define V_MIN 50 /*V eh a velocidade*/
#define V_MAX 5000
#define P_MIN 0 /*P eh a paciencia*/
#define P_MAX 100
#define HAB_MIN 1 /*HAB representa as habilidades*/
#define HAB_MAX 3
#define COORD_MIN 0 /*COORD eh a coordenada*/
#define COORD_MAX (N_TAMANHO_MUNDO - 1)
#define LOT_MIN 3 /*LOT eh a lotacao da base*/
#define LOT_MAX 10
#define HAB_N_MIN 6 /*HAB_N eh o numero de habilidades necessarias para a missao*/
#define HAB_N_MAX 10 

#include "conjunto.h"
#include "lista.h"
#include "fila.h"
#include "fprio.h"

int aleat(int min, int max);

int inicializa_heroi(struct mundo *w, int id);

int inicializa_base(struct mundo *w, int id);

int inicializa_missao(struct mundo *w, int id);

int inicializa_mundo();

#endif