#include "busca.h"

int buscaSequencial(int v[], int chave, int tam){
    int i;

    for(i=0;i<tam;i++)
        if(v[i] == chave)
            return i;

    /*se sair do laço sem ter retornado, o elemento nao foi encontrado*/
    return -1;
}

int buscaBinaria(int v[], int chave, int tam){
    int ini, meio, fim;
    ini = 0;
    fim = tam;

    while(ini<fim){
        meio = (ini+fim)/2;

        if(v[meio] == chave)
            return meio;

        if(v[meio] < chave)
            ini = meio+1;
        else if(v[meio] > chave)
            fim = meio-1;
    }

    return -1;
}