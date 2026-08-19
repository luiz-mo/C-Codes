#include "guloso.h"

void loop_guloso(Heap *h) {

    int i = extrai_min_heap(h); /*remove ponto com menor erro*/

    /* Enquanto heap não é vazio e o erro do ponto é maior ou igual à tolerância... *
     * OBS: se o menor erro do heap já for maior, todos os outros serão */
    while (i != -1 && pontos[i].erro < tolerancia) {
        /* Ponto 'anterior' e 'próximo' do ponto 'removido' são ligados - 
         * eles passam a ser adjacentes */
        int ant  = pontos[i].anterior;
        int prox = pontos[i].proximo;

        pontos[ant].proximo = prox;
        pontos[prox].anterior = ant;
        pontos[i].removido = 1;         
        
        /* Atualiza os erros dos pontos adjacentes */

        if (ant != 0)       /*se nao é o primeiro elemento*/
            pontos[ant].erro = calcula_erro(ant);

        if (prox != n - 1)  /*se nao é o ultimo elemento*/
            pontos[prox].erro = calcula_erro(prox);

        /* Atualiza o heap com os novos erros */
        atualiza_heap(h, ant);
        atualiza_heap(h, prox);

        i = extrai_min_heap(h); /* Remove ponto com menor erro */
    }
}