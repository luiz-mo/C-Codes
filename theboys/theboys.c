// programa principal do projeto "The Boys - 2025/2"
// Autor: Luiz Guilherme de Souza Mo, GRR 20252981

#include <stdio.h>
#include <stdlib.h>

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
}

struct base{
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *fila_herois;
    struct coord coord_base;
}

struct missao{
    int id;
    struct cjto_t *habilidades;
    struct coord local;
}

struct mundo{
    int n_herois;
    struct heroi *herois;
    int n_bases;
    struct base *bases;
    int n_missoes;
    struct missao *missoes;
    
}

// programa principal
int main ()
{
  // iniciar o mundo

  // executar o laço de simulação
  
  // destruir o mundo

  return (0) ;
}

