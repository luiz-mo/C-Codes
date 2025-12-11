#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "heap.h"
#include "sorts.h"

int CadastrarPaciente(struct paciente *heap[], int *tam, int N){
    const int MAX= 50; 
    char nome[MAX];
    int prioridade;

    printf("\nInsira o nome do paciente\n");
    fgets(nome, MAX, stdin); //lê o nome
    nome[strcspn(nome, "\n")] = 0; //reconhece a quebra de linha (ENTER)

    while(nome[0] == '\0'){ //Enquanto o usuário não mandar um usuário válido
        printf("Nome do paciente em branco.\n");
        printf("Insira o nome do paciente\n");
        fgets(nome, MAX, stdin); //lê o nome
        nome[strcspn(nome, "\n")] = 0; //reconhece a quebra de linha (ENTER)
    } 

    printf("\nInsira a prioridade do paciente (quanto maior o número, maior a prioridade)\n");
    scanf("%d", &prioridade);

    int c; //Serve para limpar o buffer (corredor de 'coisas' que o usuário digitou. Para não quebrar)
    while ((c=getchar()) != '\n' && c != EOF);

    int sucesso;
    sucesso = InsereNovoHeap(heap, nome, prioridade, tam, N);

    if (!sucesso) {
        printf("\nFalha ao cadastrar paciente, heap cheio ou memória insuficiente.\n");
        return 0;
    }

    printf("\nUsuário cadastrado com sucesso!\n");
    return 1;
}

void ChamarPaciente(struct paciente *heap[], int *tam){
    if(!heap||!tam)
        return;

    struct paciente *pacienteRemovido;

    printf("\nChamando próximo paciente...\n");
    pacienteRemovido= RemoveHeap(heap, tam);

    if(pacienteRemovido==NULL){
        printf("\nA fila está vazia");
        return;
    }

    printf("Paciente: %s, de prioridade %d, removido da fila\n", pacienteRemovido->nome, pacienteRemovido->prioridade);
    free(pacienteRemovido);
    pacienteRemovido=NULL;
}

void ImprimirPacientes(struct paciente *heap[], int tam){
    if(!ChecaHeap(heap,tam)){
        int comparacoes=0, trocas=0;
        Heapfy(heap, tam, &comparacoes, &trocas);
        printf("\nHeapfy fez %d comparações e %d trocas\n", comparacoes, trocas);
    }

    printf("\nImprimindo pacientes:\n");
    if (!ImprimeHeap(heap,tam))
        printf("\nHeap vazio\n");
}

void OrdenarPacientes(struct paciente *heap[], int tam){
    printf("\nOrdenando pacientes...\n");
    int comparacoes=0, trocas=0;

    HeapSort(heap, tam, &comparacoes, &trocas);
    printf("\nHeapSort fez %d comparações e %d trocas\n", comparacoes, trocas);
    
    printf("\nImprimindo pacientes ordenados:\n");
    ImprimeHeap(heap,tam);

    comparacoes = 0;
    trocas = 0;
    Heapfy(heap,tam, &comparacoes, &trocas);
    printf("\nHeapfy fez %d comparações e %d trocas para voltar o vetor a um heap\n", comparacoes, trocas);
}

void AtualizarPrioridade(struct paciente *heap[], int tam){
    char nome[50];
    const int MAX=50;
    int prioridade, x;

    printf("\nInsira o nome do paciente que deseja alterar a prioridade\n");
    fgets(nome, MAX, stdin); 
    nome[strcspn(nome, "\n")] = 0;

    printf("\nInsira a prioridade NOVA do paciente\n");
    scanf("%d", &prioridade);

    int c; 
    while ((c=getchar()) != '\n' && c != EOF);

    x= AlteraHeap(heap, nome, prioridade, tam);

    if(!x){
        printf("\nPaciente não encontrado (não existe ou foi digitado errado)");
        return;
    }
    
    printf("\nPrioridade do paciente %s, alterada!", nome);
}

void CompararSorts(){
    int *v, *w, *z; //3 vetores
    int min = -511, max = 512, i, tam = 1024, n_comp, n_trocas;

    if(!(v = malloc(sizeof(int) * (tam+1)))){
        printf("n\nao foi possivel alocar o vetor");
        return;
    }

    for(i=1;i<=tam;i++){
        v[i] = min+rand()%(max-min+1); /*max-min+1 delimita o intervalo de -511 ate 512 e min+rand() garante que o intervalo comeca em -511*/
    }

    if(!(w = malloc(sizeof(int) * (tam+1)))){
        printf("\nnao foi possivel alocar o vetor");
        return;
    } 
    
    if(!(z = malloc(sizeof(int) * (tam+1)))){
        printf("\nnao foi possivel alocar o vetor");
        return;
    } 

    memcpy(w, v, sizeof(int) * (tam+1)); /*copia o vetor v em w*/
    memcpy(z, v, sizeof(int) * (tam+1)); /*copia o vetor v em z*/

    printf("\nOrdenando com Select Sort\n");
    n_comp = 0;
    n_trocas = 0;
    SelectSort(v,tam,&n_comp,&n_trocas);
    printf("Select Sort fez %d comparacoes e %d trocas\n", n_comp, n_trocas);

    printf("\nOrdenando com Quick Sort\n");
    n_comp = 0;
    n_trocas = 0;
    QuickSort(w,1,tam,&n_comp,&n_trocas);
    printf("Quick Sort fez %d comparacoes e %d trocas\n", n_comp, n_trocas);

    printf("\nOrdenando com Heap Sort\n");
    n_comp = 0;
    n_trocas = 0;
    HeapSortInt(z,tam,&n_comp,&n_trocas);
    printf("Heap Sort fez %d comparacoes e %d trocas\n", n_comp, n_trocas);

    int operacao;

    printf("\nInsira 1 para imprimir o vetor ordenado\n");
    printf("Insira 0 para sair\n");

    scanf("%d", &operacao);

    if(operacao == 0){
        free(v);
        free(w);
        free(z);
        return;
    }

    printf("Vetor ordenado: ");
    for(i=1;i<=tam;i++)
        printf("%3d ", v[i]);

    free(v);
    free(w);
    free(z);
}

void LiberaVetor(struct paciente *heap[], int tam){
    if(!heap)
        return;

    int i;

    for(i=1;i<=tam;i++)
        free(heap[i]);

    free(heap);
}

int main(){
    int operacao, encerrar = 0, tam; //tam= numero de pacientes no vetor
    struct paciente **heap;
    const int MAX=1024; //tamanho máximo do vetor

    srand(0);

    tam=0;

    heap= InicHeap(MAX, &tam);

    do{
        printf("\n========================================================================\n");
        printf("Insira o numero correspondente a operacao desejada\n");
        printf("\n1.Cadastrar novo paciente");
        printf("\n2.Chamar proximo paciente");
        printf("\n3.Imprimir todos os pacientes em heap");
        printf("\n4.Ordenar pacientes (ordem crescente de prioridade)");
        printf("\n5.Atualizar prioridade");
        printf("\n6.Comparar algoritmos de ordenacao");
        printf("\n7.Encerrar programa\n");
        printf("\n========================================================================\n");
        scanf("%d",&operacao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch(operacao){
            case 1:
            CadastrarPaciente(heap,&tam, MAX);
            break;

            case 2:
            ChamarPaciente(heap,&tam);
            break;

            case 3:
            ImprimirPacientes(heap, tam);
            break;

            case 4:
            OrdenarPacientes(heap, tam);
            break;

            case 5:
            AtualizarPrioridade(heap, tam);
            break;

            case 6:
            CompararSorts();
            break;

            case 7:
            LiberaVetor(heap, tam);
            encerrar = 1;
            break;

            default:
            printf("Por favor, digite um numero valido");
        }
    }while(!encerrar);   
    return 0;
}
