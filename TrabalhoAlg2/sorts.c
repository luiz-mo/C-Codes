#include <stdio.h>
#include <stdlib.h>

#include "sorts.h"

int escolhePivo(int v[], int ini, int fim){
    int meio = (ini+fim)/2, aux;

    if(v[ini] > v[meio]){
        aux = v[ini];
        v[ini] = v[meio];
        v[meio] = aux;
    }

    if(v[meio] > v[fim]){
        aux = v[meio];
        v[meio] = v[fim];
        v[fim] = aux;

        if(v[ini] > v[meio]){
            aux = v[ini];
            v[ini] = v[meio];
            v[meio] = aux;
        }
    }

    return meio;
}

void Particao(int v[], int ini, int fim, int *pos_pivo, int *n_comp, int *n_trocas){
    int i = ini +1, j = fim, pivo, aux;
    *pos_pivo = escolhePivo(v,ini,fim);
    pivo = v[*pos_pivo];

    /*coloca o pivo no inicio*/
    aux = v[ini];
    v[ini] = v[*pos_pivo];
    v[*pos_pivo] = aux;

    while(i<j){
        while(i<fim && v[i] <= pivo){
            i++;
            (*n_comp)++;
        }
        while(j>ini && v[j]> pivo){
            j--;
            (*n_comp)++;
        }
        if(i<j){
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            (*n_trocas)++;
        }
    }
    v[ini] = v[j];
    v[j] = pivo;
    *pos_pivo = j;
    (*n_trocas)++;
}

void InsereHeapInt(int v[], int tam, int *n_comp, int *n_trocas){
    if(!v)
        return;

    int i=tam+1;
    int aux;

    while (i>1){
        (*n_comp)++;

        if (v[i/2] < v[i]){
            (*n_trocas)++;
            aux = v[i/2];
            v[i/2]= v[i];
            v[i] = aux;
            i= i/2;
        }

        else
            break;
    }
}

void SacodeHeapInt(int i, int tam, int v[], int *comparacoes, int *trocas){
    if(!v)
        return;

    i=i*2; //aqui está a adaptação, "i" é passado como parâmetro
    int aux;

    while (i<=tam){
        if (i< tam){
            (*comparacoes)++;
            if((v[i] < v[i+1]))
                i++;
        }
        
        (*comparacoes)++;
        if (v[i/2] >= v[i])
            break; //é heap
        
        (*trocas)++;
        aux= v[i/2];
        v[i/2]= v[i];
        v[i]= aux;
        i=i*2;
    }
}

int ChecaHeapInt(int v[], int tam){
    if(!v)
        return 0;

    int i;
    for (i=tam; i>1; i--) 
        if (v[i] > v[i/2])
            return 0;
    return 1;  
}

void HeapfyInt(int v[], int tam, int *comparacoes, int *trocas){
    if(!v)
        return;

    int i;
    for (i=1; i<tam; i++)
        InsereHeapInt (v, i, comparacoes, trocas);
}

void QuickSort(int v[], int ini, int fim, int *n_comp, int *n_trocas){
    int pos_pivo;
    if(ini<fim){
        Particao(v,ini,fim,&pos_pivo,n_comp,n_trocas);
        QuickSort(v,ini,pos_pivo - 1, n_comp, n_trocas);
        QuickSort(v, pos_pivo+1, fim, n_comp, n_trocas);
    }
}

void SelectSort(int v[], int tam, int *n_comp, int *n_trocas){
    int i, j, menor, aux;   
    for(i=1;i<tam;i++){
        menor = i;
        for(j=i+1;j<=tam;j++){
            (*n_comp)++;
            if(v[j] < v[menor])
                menor = j;
        }
        aux = v[menor];
        v[menor] = v[i];
        v[i] = aux;
        (*n_trocas)++;
    }
}

void HeapSortInt(int v[], int tam, int *n_comp, int *n_trocas){
    int aux, i;

    if(!v)
        return;

    *n_comp=0;
    *n_trocas=0;
    
    if(!ChecaHeapInt(v,tam))
        HeapfyInt(v, tam, n_comp, n_trocas);

    for (i=tam; i>1; i--) {
        (*n_trocas)++;
        aux = v[1]; 
        v[1] = v[i];
        v[i] = aux;
        SacodeHeapInt (1, i-1, v, n_comp, n_trocas);
    }
}
