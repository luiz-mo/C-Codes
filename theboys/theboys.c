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
    void *evento;
    int tipo, tempo;
    srand(0);

    w = inicializa_mundo();
    agenda_eventos(w);

    while(){
        evento = fprio_retira(w->LEF,&tipo,&tempo);
        w->relogio = tempo;
        w->eventos_tratados++;
        switch(tipo){
            case CHEGA:
                evento_chega(w,evento);
                break;
            case ESPERA:
                evento_espera(w,evento);
                break;
            case DESISTE:
                evento_desiste(w,evento);
                break;
            case AVISA:
                evento_avisa(w,evento);
                break;
            case ENTRA:
                evento_entra(w,evento);
                break;
            case SAI:
                evento_sai(w,evento);
                break;
            case VIAJA:
                evento_viaja(w,evento);
                break;
            case MORRE:
                evento_morre(w,evento);
                break;
   /*         case MISSAO:
                evento_missao(w,evento);
                break;*/
            case FIM:
                evento_fim(w);
        }
        free(evento);
    }
    
  
    // destruir o mundo

    return (0) ;
}

