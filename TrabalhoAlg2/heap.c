    #include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

//sacode o heap, elemento de heap[1] percorre o heap até se encontrar. 
//Essa versão do SacodeHeap é adaptada ao resto do código para sua reutilização
void SacodeHeap (int i, int tam, struct paciente *heap[], int *comparacoes, int *trocas){
    if(!heap)
        return;

    i=i*2; //aqui está a adaptação, "i" é passado como parâmetro
    struct paciente *AUX;

    while (i<=tam){
        if (i< tam){
            (*comparacoes)++;
            if((heap[i]->prioridade < heap[i+1]->prioridade))
                i++;
        }
        
        (*comparacoes)++;
        if (heap[i/2]->prioridade >= heap[i]->prioridade)
            break; //é heap
        
        (*trocas)++;
        AUX= heap[i/2];
        heap[i/2]= heap[i];
        heap[i]= AUX;
        i=i*2;
    }
}

//Aloca memória para o heap. 
struct paciente **InicHeap(int N, int *tam){
    if(!tam)
        return NULL;

    struct paciente **heap;
    
    if(!(heap=malloc(sizeof (struct paciente*)* (N+1))))
        return NULL;

    *tam = 0;
        
    return heap;
}

//Elemento inserido é colocado na última posição do vetor, é necessário atualizar o tamanho do tam após inserção
void InsereHeap(struct paciente *heap[], int tam, int *comparacoes, int *trocas){
    if(!heap)
        return;

    int i=tam+1;
    struct paciente *AUX;

    while (i>1){
        (*comparacoes)++;

        if (heap[i/2]->prioridade < heap[i]->prioridade){
            (*trocas)++;
            AUX= heap[i/2];
            heap[i/2]= heap[i];
            heap[i] = AUX;
            i= i/2;
        }

        else
            break;
    }
}

int InsereNovoHeap(struct paciente *heap[], char NovoNome[], int NovaPrioridade, int *tam, int N){
    if(!heap||!tam)
        return 0;

    if (*tam==N)
        return 0;
    
    struct paciente *NovoPaciente;
    int comp, troc; //inteiros não utilizados

    if (!(NovoPaciente=malloc(sizeof(struct paciente))))
        return 0;

    strcpy(NovoPaciente->nome, NovoNome);
    NovoPaciente->prioridade= NovaPrioridade;

    *tam = *tam+1;
    heap[*tam] = NovoPaciente;
    InsereHeap(heap, *tam-1, &comp, &troc);

    return 1;
}

//Remove o primeiro paciente do heap, é necessário dar free no paciente depois
struct paciente *RemoveHeap(struct paciente *heap[], int *tam){
    if(!heap||!tam||!heap[1])
        return NULL;

    if (*tam==0)
        return NULL;

    int comp, trocas; //comp e trocas não utilizados
    struct paciente *pacienteRemovido;

    pacienteRemovido = heap[1];

    if (*tam != 1)
        heap[1] = heap[*tam];
    else
        heap[1]=NULL;
    *tam = *tam-1;

    SacodeHeap(1, *tam, heap, &comp, &trocas);

    return pacienteRemovido;
}

//Heapfica um vetor através de InsereHeap
void Heapfy(struct paciente *heap[], int tam, int *comparacoes, int *trocas){
    if(!heap)
        return;

    int i;
    for (i=1; i<tam; i++)
        InsereHeap (heap, i, comparacoes, trocas);
}

//Checa se o vetor é um heap
int ChecaHeap(struct paciente *heap[], int tam){
    if(!heap)
        return 0;

    int i;
    for (i=tam; i>1; i--) 
        if (heap[i]->prioridade > heap[i/2]->prioridade)
            return 0;
    return 1;  
}

//Imprime o nome dos pacientes e sua prioridade
int ImprimeHeap(struct paciente *heap[], int tam){
    int j=1;
    
    if(!heap || !heap[j])
        return 0;

    int i;
    for (i=1; i<=tam; i++)
        printf("Paciente: %s, prioridade: %d\n", heap[i]->nome, heap[i]->prioridade);
    return 1;

}

//Ordena o heap
void HeapSort(struct paciente *heap[], int tam, int *comparacoes, int *trocas){
    if(!heap)
        return;

    int i;

    *comparacoes=0;
    *trocas=0;

    if(!ChecaHeap(heap,tam))
        Heapfy(heap, tam, comparacoes, trocas);

    struct paciente *AUX;

    for (i=tam; i>1; i--) {
        (*trocas)++;
        AUX= heap[1]; 
        heap[1] = heap[i];
        heap[i] = AUX;
        SacodeHeap (1, i-1, heap, comparacoes, trocas);
    }
}

//Altera a prioridade de um paciente no heap
int AlteraHeap(struct paciente *heap[], char nome[], int prioridade, int tam){
    if(!heap)
        return 0;

    int i=1;

    while ((i<=tam)&&(heap[i])&&(strcmp(nome, heap[i]->nome)!= 0)){
        i++;
    }

    if (i> tam || !heap[i])
        return 0;

    if (heap[i]->prioridade < prioridade){
        int comp, troc; //não utilizados

        heap[i]->prioridade = prioridade;
        InsereHeap(heap, i-1, &comp, &troc);
        return 1;
    }
    else{
        int comp, troc; //não utilizados
        heap[i]->prioridade = prioridade;
        SacodeHeap(i, tam, heap, &comp, &troc); //Motivo de SacodeHeap ser adaptado
        return 1;
    }

}