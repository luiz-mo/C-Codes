#include "sorts.h"
#include "heap.h"

void SelectSort(int v[], int n){
    int menor, i, j, aux;

    for(i=0;i < n;i++){
        menor = i;
        /*encontra o menor elemento*/
        for(j=1;i <= n;j++)
            if(v[j] < v[menor])
                menor = j;
        /*troca a posicao do menor elemento*/
        aux = v[menor];
        v[menor] = v[i];
        v[i] = aux;
    }
}

void BubbleSort(int v[], int n){
    int i, j, aux;

    for(i=0;i < n;i++)
        for(j=n;j >= i;j--)
            if(v[j] < v[j--]){
                aux = v[j];
                v[j] = v[j--];
                v[j--] = aux;
            }
}

int Particao(int v[], int ini, int fim, int pivo){
    int i, j, aux;
    i = ini;
    j = fim;

    while(i<j){
        while(i<fim && v[i] <= pivo){
            i++;
        }
        while(j>ini && v[j] >= pivo){
            j--;
        }
        if(i<j){
            aux = v[j];
            v[j] = v[i];
            v[i] = aux;
        }
    }
    v[ini] = v[j];
    v[j] = pivo;

    return j; /*pos_pivo*/
}

void QuickSort(int v[], int ini, int fim){
    int pos_pivo, pivo;

    pivo = ini;
    pos_pivo = Particao(v,ini,fim,pivo);

    QuickSort(v,ini,pos_pivo-1);
    QuickSort(v,pos_pivo+1,fim);
}

void InsertSort(int v[], int n){
    int i, j, aux;

    for(i=1;i < n;i++)
        for(j=i;j >= 0;j--)
            if(v[j] < v[j--]){
                aux = v[j];
                v[j] = v[j--];
                v[j--] = v[j];
            }
}

void MergeSort(int v[], int n){

}

void HeapSort(int v[], int n){

}

void ShellSort(int v[], int n){

}

void RadixSort(int v[], int n){

}

void CountingSort(int v[], int n){

}