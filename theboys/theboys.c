// programa principal do projeto "The Boys - 2025/2"
// Autor: Luiz Guilherme de Souza Mo, GRR 20252981

#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"
#include "lista.h"
#include "fila.h"
#include "fprio.h"
#include "entidades.h"
#include "inicializacoes.h"
#include "eventos.h"

// programa principal
int main (){
    struct mundo *w;
    int id_evento;
    srand(0);

    w = inicializa_mundo;
    agenda_eventos(w);

    while(w->relogio < T_FIM_DO_MUNDO){
        fprio_retira()
    }
    
  
    // destruir o mundo

    return (0) ;
}

